// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

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
	WidgetComponent->SetVisibility(false);
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
		if (SphereComponent)
		{
			SphereComponent->SetSphereRadius(Data->SphereRadius);
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

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AItem::Show()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(true);
	}
}

void AItem::Hide()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
}