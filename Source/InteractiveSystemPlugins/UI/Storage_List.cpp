// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage_List.h"
#include "PackListView.h"
#include "StorageDataList.h"
#include "InteractiveSystemPlugins/Actor/StorageBox.h"
#include "InteractiveSystemPlugins/Object/StorageListItemObject.h"

bool UStorage_List::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	return true;
}

void UStorage_List::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStorage_List::UpdataStorageListData_Implementation(TArray<AActor*> &StorageList)
{
	IUIPacksackInterface::UpdataStorageListData_Implementation(StorageList);
	
	if (!StorageListView)return;
	
	StorageListView->ClearListItems();
	StorageListView->ClearSelection();
	
	for (auto Itme : StorageList)
	{
		if (CastChecked<AStorageBox>(Itme))
		{
			if (CastChecked<AStorageBox>(Itme)->GetIsOpen())
			{
				UStorageListItemObject *Object = NewObject<UStorageListItemObject>();
				if (Object)
				{
					Object->SetStorageActor(Itme);
					StorageListView->AddItem(Object);
				}
			}
		}
		
	}
}
