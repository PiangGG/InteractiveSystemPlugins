// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageBox.h"

#include "InteractiveSystemPlugins/Components/StorageComponent.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "InteractiveSystemPlugins/UI/StorageDataList.h"

AStorageBox::AStorageBox()
{
	StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("StorageComponent"));
}

void AStorageBox::Pack_Implementation(AController* Controller)
{
	UE_LOG(LogTemp,Warning,TEXT("AStorageBox::Pack_Implementation"));
	
	if (!Controller)return;
	
	SetOpen(!bIsOpen);

	if (GetIsOpen())
	{
		
		if (CastChecked<UPacksackComponent>(CastChecked<APlayerController>(Controller)->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.IsBound())
		{
			CastChecked<UPacksackComponent>(CastChecked<APlayerController>(Controller)->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))->UpdatePackUI.Broadcast();
		}
	}
}

void AStorageBox::Pack_Server()
{
	Super::Pack_Server();
}

void AStorageBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStorageBox,bIsOpen);
}

bool AStorageBox::GetIsOpen()
{
	return bIsOpen;
}

void AStorageBox::SetOpen(bool bopen)
{
	bIsOpen = bopen;
}