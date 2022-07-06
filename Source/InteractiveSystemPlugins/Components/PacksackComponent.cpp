// Fill out your copyright notice in the Description page of Project Settings.


#include "PacksackComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "InteractiveSystemPlugins/Actor/Item.h"
#include "InteractiveSystemPlugins/Interface/ActorPacksackInterface.h"
#include "InteractiveSystemPlugins/UI/WBP_Packsack_Main.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UPacksackComponent::UPacksackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicated(true);
	
	
}

void UPacksackComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPacksackComponent,PackDataList)
	//DOREPLIFETIME(UPacksackComponent,PackWidget)
}

void UPacksackComponent::InitPacksackData(TArray<FPackItmeStruct> &PackDataArray)
{

	PackDataList = PackDataArray;
}

void UPacksackComponent::InitSphereComponent()
{
	
	if (GetOwberisPawn())
	{
		SphereComponent = NewObject<USphereComponent>(Owner,"SphereComponent");
		SphereComponent->SetSphereRadius(128.0f);
		Owner->AddOwnedComponent(SphereComponent);
		Owner->AddInstanceComponent(SphereComponent);
		SphereComponent->RegisterComponent();
		SphereComponent->AttachToComponent(Owner->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		SphereComponent->SetGenerateOverlapEvents(true);
		SphereComponent->SetCollisionProfileName("PackProfile");
		
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&UPacksackComponent::OnSphereComponentBeginOverlap);
		
		SphereComponent->OnComponentEndOverlap.AddDynamic(this,&UPacksackComponent::OnSphereComponentEndOverlap);

		
	}
	if (GetWorld()->GetGameInstance()->GetFirstLocalPlayerController())
	{
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->InputComponent->BindAction("Pick",EInputEvent::IE_Pressed,this,&UPacksackComponent::Pick);
	}
	if (GetWorld()->GetGameInstance()->GetFirstLocalPlayerController())
	{
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->InputComponent->BindAction("OpenPick",EInputEvent::IE_Pressed,this,&UPacksackComponent::OpenPick);
	}
}

void UPacksackComponent::PostInitProperties()
{
	Super::PostInitProperties();
	
}


void UPacksackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UpdatePackUI.AddDynamic(this,&UPacksackComponent::UPacksackComponent::UpdatePick_TimerBegin);
	
	InitSphereComponent();
}

void UPacksackComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UPacksackComponent::PickByF()
{
	Pick();
}

void UPacksackComponent::Pick()
{
	PickServer();
	if (UpdatePackUI.IsBound())
	{
		UpdatePackUI.Broadcast();
	}
}

void UPacksackComponent::PickServer_Implementation()
{
	if (CastChecked<APawn>(Owner))
	{
		if (CastChecked<APawn>(Owner)->GetController())
		{
			//if (!CastChecked<APawn>(Owner)->GetController()->IsLocalController())return;
			
			FVector StartLocation =  CastChecked<APawn>(Owner)->GetActorLocation();
			FRotator Rotation =  CastChecked<APawn>(Owner)->GetController()->GetControlRotation();
			FVector CameraForward = UKismetMathLibrary::GetForwardVector(Rotation);
			FVector EndLocation = StartLocation+CameraForward*600.0f;
			TArray<FHitResult> HitResults;
			TArray<AActor*> IgnoreArray;
			
			FCollisionQueryParams TraceParams;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACharacter::StaticClass(),IgnoreArray);
			TraceParams.AddIgnoredActors(IgnoreArray);
			TraceParams.bReturnPhysicalMaterial = false;
			//使用复杂Collision判定，逐面判定，更加准确    
			TraceParams.bTraceComplex = true;
		
			if (GetWorld()->LineTraceMultiByObjectType(HitResults,StartLocation,EndLocation,ObjectTypeQuery7,TraceParams))
			{
				//UE_LOG(LogTemp,Warning,TEXT("HitResult:%s"),*HitResults[0].GetActor()->GetName());
				if (HitResults.IsValidIndex(0))
				{
					if (IsValid(HitResults[0].GetActor()))
					{
						if (HitResults[0].GetActor()->GetClass()->ImplementsInterface(UActorPacksackInterface::StaticClass()))
						{
							IActorPacksackInterface* ActorPacksackInterface =Cast<IActorPacksackInterface>(HitResults[0].GetActor());
							if (ActorPacksackInterface)
							{
								CastChecked<AItem>(HitResults[0].GetActor())->SetOwner(Owner);
								ActorPacksackInterface->Execute_Pack(HitResults[0].GetActor(),CastChecked<APawn>(Owner)->GetController());
							}
						}
					}	
				}
			}
			else
			{
				if (GetAllOverlapActors().IsValidIndex(0))
				{
					//UE_LOG(LogTemp,Warning,TEXT("GetAllOverlapActors(0):%s"),*GetAllOverlapActors()[0]->GetName());
					if (IsValid(GetAllOverlapActors()[0]))
					{
						if (GetAllOverlapActors()[0]->GetClass()->ImplementsInterface(UActorPacksackInterface::StaticClass()))
						{
							IActorPacksackInterface* ActorPacksackInterface =Cast<IActorPacksackInterface>(GetAllOverlapActors()[0]);
							if (ActorPacksackInterface)
							{
								CastChecked<AItem>(GetAllOverlapActors()[0])->SetOwner(Owner);
								ActorPacksackInterface->Execute_Pack((GetAllOverlapActors()[0]),CastChecked<APawn>(Owner)->GetController());
							}
						}
					}
				}
			}
		}
	}
}

void UPacksackComponent::PickNetMulticast_Implementation()
{
	
}

TArray<AActor*> UPacksackComponent::GetAllOverlapActors()
{
	if (SphereComponent)
	{
		SphereComponent->GetOverlappingActors(OutOverlappingActors,AItem::StaticClass());
		return OutOverlappingActors;
	}
	OutOverlappingActors.Empty();
	
	return OutOverlappingActors;
}

void UPacksackComponent::UnPick(FPackItmeStruct &packItmeStruct)
{
	for (int i =0;i<PackDataList.Num();i++)
	{
		if (!PackDataList.IsValidIndex(i))return;
		
		if (PackDataList[i].Name == packItmeStruct.Name)
		{
			int CurrentNumber = PackDataList[i].Numbers-packItmeStruct.Numbers;
			if (CurrentNumber<=0)
			{
				PackDataList.RemoveAt(i);
				PackDataList[i].Numbers = CurrentNumber;
				//ThrowOut(FPackItmeStruct(packItmeStruct.Name,));
			}
			else
			{
				ThrowOut(packItmeStruct);
			}
			
			return;
		}
	}
	if (UpdatePackUI.IsBound())
	{
		UpdatePackUI.Broadcast();
	}
}

void UPacksackComponent::ThrowOut(FPackItmeStruct& packItmeStruct)
{
	if (GetOwner())
	{
		for (int i = 0;i<packItmeStruct.Numbers;i++)
		{
			AItem* Item = GetWorld()->SpawnActor<AItem>(packItmeStruct.ItemClass,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation());
			Item->Name = packItmeStruct.Name.ToString();
		}
	}
	
}


void UPacksackComponent::OpenPick()
{
	if (!PackWidget)
	{
		if (Owner)
		{
			if (!CastChecked<APawn>(Owner)->GetController())return;
			
			if (CastChecked<APawn>(Owner)->GetController()->IsLocalPlayerController())
			{
				PackWidget = CreateWidget<UUserWidget>(CastChecked<APlayerController>(CastChecked<APawn>(Owner)->GetController()),WBP_Packsack_Main);
				if (PackWidget)
				{
					PackWidget->AddToViewport();
				
					if (UpdatePackUI.IsBound())
					{
						UpdatePackUI.Broadcast();
					}
				}
			}
		}
	}
	else
	{
		PackWidget->RemoveFromViewport();
		PackWidget = nullptr;
		//UpdatePick_TimerEnd();
	}
}

void UPacksackComponent::UpdatePick()
{
	
	if (!CastChecked<APawn>(Owner))return;
	if (!CastChecked<APawn>(Owner)->GetController())return;
	if (!CastChecked<APawn>(Owner)->GetController()->IsPlayerController())return;
	
	
	if (!PackWidget)return;
	
	if (PackWidget->GetClass()->ImplementsInterface(UUIPacksackInterface::StaticClass()))
	{
		IUIPacksackInterface* IPacksackInterface = Cast<IUIPacksackInterface>(PackWidget);
		if (IPacksackInterface)
		{
			IPacksackInterface->Execute_UpdataUI(PackWidget,this);
			UpdatePick_TimerEnd();
		}
	}
	//UpdatePick_Server();
}

void UPacksackComponent::UpdatePick_Server_Implementation()
{
	UpdatePick_NetMulticast();
}

bool UPacksackComponent::UpdatePick_Server_Validate()
{
	return true;
}

void UPacksackComponent::UpdatePick_NetMulticast_Implementation()
{
	if (!CastChecked<APawn>(Owner))return;
	if (!CastChecked<APawn>(Owner)->GetController())return;
	if (!CastChecked<APawn>(Owner)->GetController()->IsPlayerController())return;
	
	if (!PackWidget)return;
	
	if (PackWidget->GetClass()->ImplementsInterface(UUIPacksackInterface::StaticClass()))
	{
		IUIPacksackInterface* IPacksackInterface = Cast<IUIPacksackInterface>(PackWidget);
		if (IPacksackInterface)
		{
			IPacksackInterface->Execute_UpdataUI(PackWidget,this);
		}
	}
}

void UPacksackComponent::UpdatePick_TimerBegin()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdatePack,this,&UPacksackComponent::UpdatePick,0.001f,true,0.2f);
	}
}

void UPacksackComponent::UpdatePick_TimerEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdatePack);
}

bool UPacksackComponent::GetOwberisPawn()
{
	Owner = CastChecked<APawn>(GetOwner());
	if (Owner)
	{
		return  true;
	}
	return false;
}

void UPacksackComponent::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("OnSphereComponentBeginOverlap:%s"),*OtherActor->GetName());
	if (Cast<AItem>(OtherActor))
	{
		Cast<AItem>(OtherActor)->Show(CastChecked<APawn>(GetOwner()));
	}
}

void UPacksackComponent::OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("OnSphereComponentEndOverlap:%s"),*OtherActor->GetName());
	if (Cast<AItem>(OtherActor))
	{
		Cast<AItem>(OtherActor)->Hide(CastChecked<APawn>(GetOwner()));
	}
}

void UPacksackComponent::BeginDestroy()
{
	Super::BeginDestroy();
	
	UpdatePackUI.Clear();
}

void UPacksackComponent::SetTargetPackActorTip()
{
	if (CastChecked<APawn>(Owner))
	{
		if (CastChecked<APawn>(Owner)->GetController())
		{
			FVector StartLocation =  CastChecked<APawn>(Owner)->GetActorLocation();
			FRotator Rotation =  CastChecked<APawn>(Owner)->GetController()->GetControlRotation();
			FVector CameraForward = UKismetMathLibrary::GetForwardVector(Rotation);
			FVector EndLocation = StartLocation+CameraForward*600.0f;
			TArray<FHitResult> HitResults;
			TArray<AActor*> IgnoreArray;
			
			FCollisionQueryParams TraceParams;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACharacter::StaticClass(),IgnoreArray);
			TraceParams.AddIgnoredActors(IgnoreArray);
			TraceParams.bReturnPhysicalMaterial = false;
			//使用复杂Collision判定，逐面判定，更加准确    
			TraceParams.bTraceComplex = false;

			
			if (GetWorld()->LineTraceMultiByObjectType(HitResults,StartLocation,EndLocation,ObjectTypeQuery7,TraceParams))
			{
				if (HitResults.IsValidIndex(0))
				{
					if (HitResults[0].GetActor()->GetClass()->ImplementsInterface(UActorPacksackInterface::StaticClass()))
					{
						LastTargetPackActor = CurrentTargetPackActor;
						CurrentTargetPackActor = HitResults[0].GetActor();
					}
				}
			}
			else
			{
				if (GetAllOverlapActors().IsValidIndex(0))
				{
					if (GetAllOverlapActors()[0]->GetClass()->ImplementsInterface(UActorPacksackInterface::StaticClass()))
					{
						LastTargetPackActor = CurrentTargetPackActor;
						CurrentTargetPackActor = GetAllOverlapActors()[0];
					}
				}
				else
				{
					CurrentTargetPackActor = nullptr;
				}
			}
			if (LastTargetPackActor)
			{
				IActorPacksackInterface* ActorPacksackInterface =Cast<IActorPacksackInterface>(LastTargetPackActor);
				if (ActorPacksackInterface)
				{
					ActorPacksackInterface->Execute_TipActor(CastChecked<AItem>(LastTargetPackActor),CastChecked<APawn>(Owner)->GetController(),false,1);
				}
			}
			
			if (CurrentTargetPackActor)
			{
				IActorPacksackInterface* ActorPacksackInterface =Cast<IActorPacksackInterface>(CurrentTargetPackActor);
				if (ActorPacksackInterface)
				{
					ActorPacksackInterface->Execute_TipActor(CastChecked<AItem>(CurrentTargetPackActor),CastChecked<APawn>(Owner)->GetController(),true,255);
				}
			}
			else
			{
				
			}
		}
	}
	/*if (CurrentTargetPackActor)
	{
		UE_LOG(LogTemp,Warning,TEXT("CurrentTargetPackActor:%s"),*CurrentTargetPackActor->GetName());
	}
	if (LastTargetPackActor)
	{
		UE_LOG(LogTemp,Warning,TEXT("CurrentTargetPackActor:%s"),*LastTargetPackActor->GetName());
	}*/
}


void UPacksackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//tick 目标 Actor
	SetTargetPackActorTip();
}

