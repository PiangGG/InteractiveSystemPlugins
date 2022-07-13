// Fill out your copyright notice in the Description page of Project Settings.


#include "PacksackComponent.h"

#include "StorageComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "InteractiveSystemPlugins/Actor/Item.h"
#include "InteractiveSystemPlugins/Actor/StorageBox.h"
#include "InteractiveSystemPlugins/Interface/ActorPacksackInterface.h"
#include "InteractiveSystemPlugins/Object/StorageListItemObject.h"
#include "InteractiveSystemPlugins/Subsystem/InteractiveSubsystem.h"
#include "InteractiveSystemPlugins/UI/WBP_Packsack_Main.h"
#include "InteractiveSystemPlugins/UI/WBP_Pack_RemoveItem_Box.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

UPacksackComponent::UPacksackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//SetIsReplicated(true);
}

void UPacksackComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPacksackComponent,PackDataList)
	//DOREPLIFETIME(UPacksackComponent,PackItmeStruct)
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
		
		if (GetWorld()->GetGameInstance()->GetFirstLocalPlayerController())
		{
			GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->InputComponent->BindAction("Pick",EInputEvent::IE_Pressed,this,&UPacksackComponent::Pick);
		}
		if (GetWorld()->GetGameInstance()->GetFirstLocalPlayerController())
		{
			GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->InputComponent->BindAction("OpenPick",EInputEvent::IE_Pressed,this,&UPacksackComponent::OpenPick);
		}
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

void UPacksackComponent::UnPickShowSelected(const FPackItmeStruct& packItmeStruct)
{
	if (packItmeStruct.Numbers<=1)
	{
		ThrowOut(packItmeStruct);
		if (UpdatePackUI.IsBound())
		{
			UpdatePackUI.Broadcast();
		}
	}
	else
	{
		if (CastChecked<UWBP_Packsack_Main>(PackWidget))
		{
			CastChecked<UWBP_Packsack_Main>(PackWidget)->ShowRemoveItemBox(this,packItmeStruct);
			if (UpdatePackUI.IsBound())
			{
				UpdatePackUI.Broadcast();
			}
		}
		else
		{
			ThrowOut(packItmeStruct);
			if (UpdatePackUI.IsBound())
			{
				UpdatePackUI.Broadcast();
			}
		}
	}
}


void UPacksackComponent::UnPickOptionSeleted(bool OptionSeleted,FPackItmeStruct& packItmeStruct)
{
	if (OptionSeleted&&CastChecked<UWBP_Packsack_Main>(PackWidget)->RemoveItemBox)
	{
		int Numbers = packItmeStruct.Numbers;
		
		packItmeStruct.Numbers = CastChecked<UWBP_Packsack_Main>(PackWidget)->RemoveItemBox->RemoveNumber;
		
		Numbers -= packItmeStruct.Numbers;
		if (Numbers>0)
		{
			PackDataList.Add(FPackItmeStruct(packItmeStruct.ItemClass,Numbers,packItmeStruct.Name));
		}
		ThrowOut(packItmeStruct);
	}
	else
	{
		ThrowOut(packItmeStruct);
	}
	if (UpdatePackUI.IsBound())
	{
		UpdatePackUI.Broadcast();
	}
	SelectedOption.Unbind();
	if (CastChecked<UWBP_Packsack_Main>(PackWidget))
	{
		CastChecked<UWBP_Packsack_Main>(PackWidget)->HideRemoveItemBox(this);
	}
}

void UPacksackComponent::UnPick(const FPackItmeStruct& packItmeStruct)
{
	UnPick_Server(packItmeStruct);
}

void UPacksackComponent::UnPick_Server_Implementation(const FPackItmeStruct& packItmeStruct)
{
	PackItmeStruct = MakeShareable(new FPackItmeStruct(packItmeStruct));
	if (!PackItmeStruct)return;
	
	for (int i =0;i<PackDataList.Num();i++)
	{
		if (!PackDataList.IsValidIndex(i))return;
		
		if (PackDataList[i].Name == PackItmeStruct->Name)
		{
			int CurrentNumber = PackDataList[i].Numbers-PackItmeStruct->Numbers;
			if (CurrentNumber<=0)
			{
				ThrowOut(PackDataList[i]);
				PackDataList.RemoveAt(i);
			}
			else
			{
				PackDataList[i].Numbers = CurrentNumber;
				ThrowOut(*PackItmeStruct);
			}
			if (UpdatePackUI.IsBound())
			{
				UpdatePackUI.Broadcast();
			}
			return;
		}
	}
}

bool UPacksackComponent::UnPick_Server_Validate(const FPackItmeStruct& packItmeStruct)
{
	return true;
}

void UPacksackComponent::ThrowOut(const FPackItmeStruct &packItmeStruct)
{
	ThrowOut_Server(packItmeStruct);
}

void UPacksackComponent::ThrowOut_Server_Implementation(const FPackItmeStruct &packItmeStruct)
{
	if (GetOwner())
	{
		for (int i = 0;i<packItmeStruct.Numbers;i++)
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			auto* Item = GetWorld()->SpawnActor<AItem>(packItmeStruct.ItemClass,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation(),ActorSpawnParameters);

			if (Item)
			{
				Item->Name = packItmeStruct.Name.ToString();
				CastChecked<AItem>(Item)->Init(packItmeStruct.Name);
			}
		}
	}
}

bool UPacksackComponent::ThrowOut_Server_Validate(const FPackItmeStruct &packItmeStruct)
{
	return  true;
}


void UPacksackComponent::Picks(const FPackItmeStruct& packItmeStruct)
{

	FPackItmeDataStruct* Data = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UInteractiveSubsystem>()->GetStructData(packItmeStruct);
	if (!Data)return;
	
	if (Data->bRepeat)
	{
		for (auto Itme : PackDataList)
		{
			if (Itme.Name == packItmeStruct.Name)
			{
				Itme.Numbers+=packItmeStruct.Numbers;
				
				if (UpdatePackUI.IsBound())
				{
					UpdatePackUI.Broadcast();
				}
				return;
			}
		}
		PackDataList.Add(packItmeStruct);
		if (UpdatePackUI.IsBound())
		{
			UpdatePackUI.Broadcast();
		}
		return;
	}
	else
	{
		PackDataList.Add(packItmeStruct);
		if (UpdatePackUI.IsBound())
		{
			UpdatePackUI.Broadcast();
		}
		return;
	}
	
}

void UPacksackComponent::OpenPick()
{
	if (!PackWidget)
	{
		if (Owner)
		{
			if (!CastChecked<APawn>(Owner)->GetController())return;
			//CastChecked<APlayerController>(CastChecked<APawn>(Owner)->GetController())->SetMouseCursorWidget(EMouseCursor::Default,PackWidget);
			CastChecked<APlayerController>(CastChecked<APawn>(Owner)->GetController())->bShowMouseCursor = true;
			if (CastChecked<APawn>(Owner)->GetController()->IsLocalPlayerController())
			{
				PackWidget = CreateWidget<UUserWidget>(CastChecked<APlayerController>(CastChecked<APawn>(Owner)->GetController()),WBP_Packsack_Main);
				if (PackWidget)
				{
					IUIPacksackInterface*UIPacksackInterfac = CastChecked<IUIPacksackInterface>(PackWidget);
					if (UIPacksackInterfac)
					{
						UIPacksackInterfac->Execute_SetWidgetOwner(PackWidget,Owner);
					}
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
		
		if (!CastChecked<APawn>(Owner)->GetController())return;
		CastChecked<APlayerController>(CastChecked<APawn>(Owner)->GetController())->bShowMouseCursor = false;
		
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
	if (GetOwner()==nullptr)return false;
	Owner = CastChecked<APawn>(GetOwner());
	if (Owner!=nullptr)
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
	if (UpdatePackUI.IsBound())
	{
		UpdatePackUI.Broadcast();
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

	if (UpdatePackUI.IsBound())
	{
		UpdatePackUI.Broadcast();
	}
}

void UPacksackComponent::BeginDestroy()
{
	Super::BeginDestroy();
	
	UpdatePackUI.Clear();
}

void UPacksackComponent::SetTargetPackActorTip()
{
	if (GetOwberisPawn()==false)return;
	
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

TArray<AActor*>& UPacksackComponent::GetOverlapStorageBox()
{
	if (SphereComponent)
	{
		SphereComponent->GetOverlappingActors(OverlapStorageBox,AStorageBox::StaticClass());
		return OverlapStorageBox;
	}
	return OverlapStorageBox;
}

TArray<FPackItmeStruct> UPacksackComponent::GetDatas_Implementation()
{
	return PackDataList;
}

void UPacksackComponent::UpdataData_Implementation(int Index)
{
	IObjectPacksackInterface::UpdataData_Implementation(Index);
	
	if (PackDataList.IsValidIndex(Index))
	{
		PackDataList.RemoveAt(Index);
	}
	
}

void UPacksackComponent::ReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct)
{
	IObjectPacksackInterface::ReMoveItem_Implementation(packItmeStruct);

	UnPickShowSelected(packItmeStruct);
	//ThrowOut(packItmeStruct);
}

void UPacksackComponent::AddItem_Implementation(const FPackItmeStruct& packItmeStruct)
{
	IObjectPacksackInterface::AddItem_Implementation(packItmeStruct);

	if (true)
	{
		
	}
}

void UPacksackComponent::UnReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct)
{
	IObjectPacksackInterface::UnReMoveItem_Implementation(packItmeStruct);
	
	PackDataList.Add(packItmeStruct);
}

