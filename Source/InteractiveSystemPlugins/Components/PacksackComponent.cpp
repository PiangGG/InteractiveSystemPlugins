// Fill out your copyright notice in the Description page of Project Settings.


#include "PacksackComponent.h"
#include "Components/SphereComponent.h"
#include "InteractiveSystemPlugins/Actor/Item.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UPacksackComponent::UPacksackComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicated(true);
}

void UPacksackComponent::InitPacksackData(TArray<FPackItmeStruct*> &PackDataArray)
{
	PackDataList.Empty();
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

		if (Owner->InputComponent)
		{
			Owner->InputComponent->BindAction("Pick",EInputEvent::IE_Pressed,this,&UPacksackComponent::Pick);
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
	
	InitSphereComponent();
}

void UPacksackComponent::InitializeComponent()
{
	Super::InitializeComponent();

	
}

void UPacksackComponent::Pick()
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
			DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Red);

			FCollisionQueryParams TraceParams;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawn::StaticClass(),IgnoreArray);
			TraceParams.AddIgnoredActors(IgnoreArray);
			TraceParams.bReturnPhysicalMaterial = false;
			//使用复杂Collision判定，逐面判定，更加准确    
			TraceParams.bTraceComplex = true;
		
			if (GetWorld()->LineTraceMultiByObjectType(HitResults,StartLocation,EndLocation,ObjectTypeQuery7,TraceParams))
			{
				UE_LOG(LogTemp,Warning,TEXT("HitResult:%s"),*HitResults[0].GetActor()->GetName());
			}
			else
			{
				if (GetAllOverlapActors().IsValidIndex(0))
				{
					UE_LOG(LogTemp,Warning,TEXT("GetAllOverlapActors(0):%s"),*GetAllOverlapActors()[0]->GetName());
				}
			}
		}
		
	}
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

void UPacksackComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPacksackComponent,PackDataList)
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
		Cast<AItem>(OtherActor)->Show();
	}
}

void UPacksackComponent::OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("OnSphereComponentEndOverlap:%s"),*OtherActor->GetName());
	if (Cast<AItem>(OtherActor))
	{
		Cast<AItem>(OtherActor)->Hide();
	}
}


void UPacksackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

