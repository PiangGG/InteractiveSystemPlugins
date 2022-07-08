// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageBox.h"

#include "InteractiveSystemPlugins/Components/StorageComponent.h"

AStorageBox::AStorageBox()
{
	StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("StorageComponent"));
}

void AStorageBox::Pack_Implementation(AController* Controller)
{
	UE_LOG(LogTemp,Warning,TEXT("AStorageBox::Pack_Implementation"));
	
	if (!Controller)return;

	if (StorageComponent)
	{
		StorageComponent->StorageDataList;
	}
	
}
