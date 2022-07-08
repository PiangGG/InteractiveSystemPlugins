// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageDataList.h"

#include "PackListView.h"
#include "PackTileView.h"
#include "Components/NamedSlot.h"
#include "InteractiveSystemPlugins/Actor/StorageBox.h"
#include "InteractiveSystemPlugins/Components/StorageComponent.h"
#include "InteractiveSystemPlugins/Object/Packsack_List_Item_Object.h"

TArray<FPackItmeStruct> UStorageDataList::GetStorageDataList_Implementation()
{
	if (CastChecked<AStorageBox>(theOwner))
	{
		return CastChecked<AStorageBox>(theOwner)->StorageComponent->StorageDataList;
	}
	if (CastChecked<APawn>(theOwner))
	{
		if (CastChecked<APawn>(theOwner)->GetComponentByClass(UPacksackComponent::StaticClass()))
		{
			return CastChecked<UPacksackComponent>(CastChecked<APawn>(theOwner)->GetComponentByClass(UPacksackComponent::StaticClass()))->PackDataList;
		}
	}
	return IUIPacksackInterface::GetStorageDataList_Implementation();
}

AActor* UStorageDataList::GetWidgetOwner_Implementation()
{
	return theOwner;
}

void UStorageDataList::UpdataUIData_Implementation(TArray<FPackItmeStruct>& StorageDataList)
{
	IUIPacksackInterface::UpdataUIData_Implementation(StorageDataList);
	if (!GetListView())return;
	
	GetListView()->ClearListItems();
	GetListView()->ClearSelection();
	
	for (auto Itme : StorageDataList)
	{
		UPacksack_List_Item_Object *Object = NewObject<UPacksack_List_Item_Object>();
		Object->SetPackItme(Itme);
		GetListView()->AddItem(Object);
	}
}

void UStorageDataList::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (NamedSlot)
	{
		NamedSlot->ClearChildren();
		
		switch (ListType)
		{
		case EPackListType::List:
			if (PackListView && PackTileView)
				PackListView->SetVisibility(ESlateVisibility::Visible);
			PackTileView->SetVisibility(ESlateVisibility::Hidden);
			NamedSlot->AddChild(PackListView);
			PackListView->SetWidgetEntry(ListItem);
			break;
		case EPackListType::Tile:
			if (PackListView && PackTileView)
				PackListView->SetVisibility(ESlateVisibility::Hidden);
			PackTileView->SetVisibility(ESlateVisibility::Visible);
			NamedSlot->AddChild(PackTileView);
			PackTileView->SetWidgetEntry(ListItem);
			break;
		default:
			break;;
		}
	}
}

UListView* UStorageDataList::GetListView()
{
	switch (ListType)
	{
	case EPackListType::List:
		return PackListView;
	case EPackListType::Tile:
		return PackTileView;
	default:
		return nullptr;
	}
}
