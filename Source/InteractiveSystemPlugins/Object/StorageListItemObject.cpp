// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageListItemObject.h"

#include "InteractiveSystemPlugins/Components/StorageComponent.h"

void UStorageListItemObject::SetStorageActor(AActor* Actor)
{
	StorageActor = Actor;
}

AActor* UStorageListItemObject::GetStorageActor()
{
	return StorageActor;
}

TArray<FPackItmeStruct> UStorageListItemObject::GetObjectDatas_Implementation(UObject* Object)
{
	if (!StorageActor)return IObjectPacksackInterface::GetObjectDatas_Implementation(Object);
	
	
	UStorageComponent* StorageComponent =CastChecked<UStorageComponent>(CastChecked<AActor>(StorageActor)->GetComponentByClass(UStorageComponent::StaticClass()));
	if (StorageComponent)
	{
		return 	StorageComponent->Data;
	}
	return IObjectPacksackInterface::GetObjectDatas_Implementation(Object);
}

TArray<FPackItmeStruct>& UStorageListItemObject::GetObjectDatasbyRef()
{
	return CastChecked<UStorageComponent>(CastChecked<AActor>(StorageActor)->GetComponentByClass(UStorageComponent::StaticClass()))->Data;
}

void UStorageListItemObject::SetEntryWidget_Implementation(UUserWidget* UserWidget)
{
	IObjectPacksackInterface::SetEntryWidget_Implementation(UserWidget);

	userwidget = UserWidget;
}

UUserWidget* UStorageListItemObject::GetEntryWidget_Implementation()
{
	return userwidget;
}

void UStorageListItemObject::SetWidgetOwner_Implementation(AActor* actor)
{
	IUIPacksackInterface::SetWidgetOwner_Implementation(actor);
	StorageActor = actor;
}

AActor* UStorageListItemObject::GetWidgetOwner_Implementation()
{
	if (StorageActor)
	{
		return StorageActor;
	}
	return IUIPacksackInterface::GetWidgetOwner_Implementation();
}

void UStorageListItemObject::SetParentWidget_Implementation(UUserWidget* parent)
{
	IUIPacksackInterface::SetParentWidget_Implementation(parent);
	
}

UUserWidget* UStorageListItemObject::GetParentWidget_Implementation()
{
	return IUIPacksackInterface::GetParentWidget_Implementation();
}

FPackItmeStruct UStorageListItemObject::GetPackItmeStruct_Implementation()
{
	return IUIPacksackInterface::GetPackItmeStruct_Implementation();
}

