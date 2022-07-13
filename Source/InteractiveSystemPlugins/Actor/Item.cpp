// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractiveSystemPlugins/Components/PacksackComponent.h"
#include "InteractiveSystemPlugins/Data/PackItemData.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemList(TEXT("DataTable'/InteractiveSystemPlugins/PacItemkList/DT_PackItemList.DT_PackItemList'"));
	
	DT = ItemList.Object;

   

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionProfileName("PackProfile");
	SphereComponent->SetupAttachment(SceneComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetIsReplicated(false);

	bReplicates = true;
	SetReplicates(true);
	SetReplicateMovement(true);
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AItem::Init()
{
	if (DT)
	{
		Data = DT->FindRow<FPackItmeDataStruct>(*Name,TEXT(""));
	}
	
	if (Data)
	{
		if (SceneComponent)
		{
			SetRootComponent(SceneComponent);
		}
		if (SphereComponent)
		{
			SphereComponent->SetSphereRadius(Data->SphereRadius);
			//SphereComponent->SetupAttachment(SceneComponent);
		}
		if (Data->Mesh_SK)
		{
		
		}

		if (Data->Mesh_SM)
		{
			
			UStaticMeshComponent * Mesh_SM = NewObject<UStaticMeshComponent>(this,"Mesh_SM");
			AddInstanceComponent(Mesh_SM);
			AddOwnedComponent(Mesh_SM);
			Mesh_SM->RegisterComponent();
			Mesh_SM->SetStaticMesh(Data->Mesh_SM);
			Mesh_SM->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
			SetRootComponent(Mesh_SM);
			
			if (Mesh_SM)
			{
				Mesh_SM->SetSimulatePhysics(Data->bSimulate);
			}
			
			if (SphereComponent)
			{
				SphereComponent->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
				SphereComponent->SetRelativeLocation(FVector(0));
			}
			
			if (WidgetComponent&&Data->ShowUI)
			{
				if (SphereComponent)
				{
					WidgetComponent->AttachToComponent(SphereComponent,FAttachmentTransformRules::KeepRelativeTransform);
					WidgetComponent->SetRelativeLocation(FVector(0));
				}
				
				ShowUI = CreateWidget<UUserWidget>(GetWorld(),Data->ShowUI);
				if (ShowUI)
				{
					WidgetComponent->SetWidget(ShowUI);
				}
			}
		}
	}
}

void AItem::Init(FName name)
{
	Init_Server(name);
}

void AItem::Init_Server_Implementation(FName name)
{
	Init_NetMulticast(name);
}

bool AItem::Init_Server_Validate(FName name)
{
	return true;
}

void AItem::Init_NetMulticast_Implementation(FName name)
{
	if (DT)
	{
		Data = DT->FindRow<FPackItmeDataStruct>(name,TEXT(""));
	}
	
	if (Data)
	{
		if (SceneComponent)
		{
			SetRootComponent(SceneComponent);
		}
		
		if (SphereComponent)
		{
			SphereComponent->SetSphereRadius(Data->SphereRadius);
			//SphereComponent->SetupAttachment(SceneComponent);
		}
		
		if (Data->Mesh_SK)
		{
		
		}

		if (Data->Mesh_SM)
		{
			
			UStaticMeshComponent * Mesh_SM = NewObject<UStaticMeshComponent>(this,"Mesh_SM");
			if (Mesh_SM)
			{
				AddInstanceComponent(Mesh_SM);
				AddOwnedComponent(Mesh_SM);
				Mesh_SM->RegisterComponent();
				Mesh_SM->SetStaticMesh(Data->Mesh_SM);
				if (Mesh_SM!=GetRootComponent())
				{
					Mesh_SM->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
				}
				SetRootComponent(Mesh_SM);
				Mesh_SM->SetSimulatePhysics(Data->bSimulate);
			}
			
			if (SphereComponent)
			{
				SphereComponent->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
				SphereComponent->SetRelativeLocation(FVector(0));
			}
			
			if (WidgetComponent&&Data->ShowUI)
			{
				if (SphereComponent)
				{
					WidgetComponent->AttachToComponent(SphereComponent,FAttachmentTransformRules::KeepRelativeTransform);
					WidgetComponent->SetRelativeLocation(FVector(0));
				}
				
				ShowUI = CreateWidget<UUserWidget>(GetWorld(),Data->ShowUI);
				if (ShowUI)
				{
					WidgetComponent->SetWidget(ShowUI);
				}
			}
		}
	}
}

bool AItem::Init_NetMulticast_Validate(FName name)
{
	return true;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AItem::Show(APawn* Pawn)
{
	if (!Pawn||!Pawn->GetController()||!Pawn->GetController()->IsLocalController())return;
	
	if (IsValid(WidgetComponent))
	{
		WidgetComponent->SetVisibility(true);
	}
}

void AItem::Hide(APawn* Pawn)
{
	if (!Pawn||!Pawn->GetController()||!Pawn->GetController()->IsLocalController())return;
	
	if (IsValid(WidgetComponent))
	{
		WidgetComponent->SetVisibility(false);
	}
	
}

void AItem::Pack_Implementation(AController* Controller)
{
	this->Destroy();
	if (Controller)
	{
		if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass())))
		{
			if (Data->bRepeat)
			{
				FName name = FName(Name);
				
				for (int i = 0;i<CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.Num();i++)
				{
					if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.IsValidIndex(i))
					{
						if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList[i].Name == name)
						{
							CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.Insert(FPackItmeStruct(CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList[i].ItemClass,CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList[i].Numbers++,CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList[i].Name),i);
							CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.RemoveAt(i++);
							if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.IsBound())
							{
								CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.Broadcast();
							}
							return;
						}
					}
					
				}
				CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.Add(FPackItmeStruct(this->StaticClass(),1,name));
				if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.IsBound())
				{
					CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.Broadcast();
				}
				
				return;
			}
			else
			{
				FName name = FName(Name);
				CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList.Add(FPackItmeStruct(this->StaticClass(),1,name));
				if (CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.IsBound())
				{
					CastChecked<UPacksackComponent>(Controller->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.Broadcast();
				}
				return;
			}
		}
	}
}

void AItem::TipActor_Implementation(AController* Controller,bool bTip,int Value)
{
	IActorPacksackInterface::TipActor_Implementation(Controller,bTip,Value);
	
	UStaticMeshComponent*Mesh =CastChecked<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(bTip);
		Value = FMath::Clamp(Value,1,255);
		Mesh->SetCustomDepthStencilValue(Value);
	}
}

void AItem::Pack_Client_Implementation()
{
	Pack_Server();
}

void AItem::Pack_Server_Implementation()
{
	Pack_NetMulticast();
}
bool AItem::Pack_Server_Validate()
{
	return true;
}

void AItem::Pack_NetMulticast_Implementation()
{
	SetActorLocation(FVector(0));
}