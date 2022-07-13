// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageDataList.h"

#include "PackListView.h"
#include "PackTileView.h"
#include "Components/NamedSlot.h"
#include "InteractiveSystemPlugins/Actor/StorageBox.h"
#include "InteractiveSystemPlugins/Components/StorageComponent.h"
#include "InteractiveSystemPlugins/Object/PackItemDragDropOperation.h"
#include "InteractiveSystemPlugins/Object/Packsack_List_Item_Object.h"

TArray<FPackItmeStruct> UStorageDataList::GetStorageDataList_Implementation()
{
	if (CastChecked<AStorageBox>(theOwner))
	{
		return CastChecked<AStorageBox>(theOwner)->StorageComponent->Data;
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

void UStorageDataList::SetWidgetOwner_Implementation(AActor* actor)
{
	IUIPacksackInterface::SetWidgetOwner_Implementation(actor);
	theOwner = actor;
}

void UStorageDataList::SetParentWidget_Implementation(UUserWidget* parent)
{
	IUIPacksackInterface::SetParentWidget_Implementation(parent);
	
	Parent = parent;
}

UUserWidget* UStorageDataList::GetParentWidget_Implementation()
{
	if (Parent)
	{
		return Parent;
	}
	return IUIPacksackInterface::GetParentWidget_Implementation();
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

		IUIPacksackInterface * UIPacksackInterface = CastChecked<IUIPacksackInterface>(Object);
		IUIPacksackInterface * UIPacksackInterface2 = CastChecked<IUIPacksackInterface>(this);
		if (UIPacksackInterface&&UIPacksackInterface2)
		{
			UIPacksackInterface->Execute_SetWidgetOwner(Object,UIPacksackInterface2->Execute_GetWidgetOwner(this));
			UIPacksackInterface->Execute_SetParentWidget(Object,this);
		}
		Object->SetPackItme(Itme);
		GetListView()->AddItem(Object);
	}
}


void UStorageDataList::UIUpdata(TArray<FPackItmeStruct> Data)
{
	
	if (!GetListView())return;
	
	GetListView()->ClearListItems();
	GetListView()->ClearSelection();
	
	for (auto Itme :  Data)
	{
		UPacksack_List_Item_Object *Object = NewObject<UPacksack_List_Item_Object>();
		if(Object)
		{
			IUIPacksackInterface * UIPacksackInterface = CastChecked<IUIPacksackInterface>(Object);
			IUIPacksackInterface * UIPacksackInterface2 = CastChecked<IUIPacksackInterface>(this);
			if (UIPacksackInterface&&UIPacksackInterface2)
			{
				UIPacksackInterface->Execute_SetWidgetOwner(Object,UIPacksackInterface2->Execute_GetWidgetOwner(this));
				UIPacksackInterface->Execute_SetParentWidget(Object,this);
			}
			Object->SetPackItme(Itme);
			GetListView()->AddItem(Object);
		}
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

bool UStorageDataList::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UPackItemDragDropOperation *DragDropOperation = Cast<UPackItemDragDropOperation>(InOperation);

	if (InOperation)
	{
		UWBP_Packsack_List_Item* DragShowUI =CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload);
		
		if (DragShowUI)
		{
			IUIPacksackInterface *UIPacksackInterface = Cast<IUIPacksackInterface>(DragShowUI);
			IUIPacksackInterface *UIPacksackInterface2 = Cast<IUIPacksackInterface>(CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload));
			if (UIPacksackInterface&&UIPacksackInterface2)
			{
				//if (UIPacksackInterface->Execute_GetParentWidget(DragShowUI)==UIPacksackInterface2->Execute_GetParentWidget(CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload)))return false;
				
				FPackItmeStruct PackItmeStruct =  UIPacksackInterface->Execute_GetPackItmeStruct(DragShowUI);
				AActor* Actor = Execute_GetWidgetOwner(this);
				if (Actor)
				{
					/*APawn * Pawn = CastChecked<APawn>(Actor);
					if (Pawn)
					{
						if (CastChecked<UPacksackComponent>(CastChecked<APawn>(Pawn)->GetComponentByClass(UPacksackComponent::StaticClass())))
						{
							CastChecked<UPacksackComponent>(CastChecked<APawn>(Pawn)->GetComponentByClass(UPacksackComponent::StaticClass()))->Picks(PackItmeStruct);
							return true;
						}
						
					}
					
					AStorageBox * StorageBox = CastChecked<AStorageBox>(Actor);
					if (StorageBox)
					{
						IObjectPacksackInterface*ObjectPacksackInterface = CastChecked<IObjectPacksackInterface>()
						CastChecked<UStorageComponent>(CastChecked<AStorageBox>(StorageBox)->GetComponentByClass(UStorageComponent::StaticClass()));
						
						return true;
					}*/
					TArray<UActorComponent*>Components = Actor->GetComponentsByInterface(UObjectPacksackInterface::StaticClass());
		
					if (Components.IsValidIndex(0))
					{
						IObjectPacksackInterface*ObjectPacksackInterface = CastChecked<IObjectPacksackInterface>(Components[0]);
						
						if (ObjectPacksackInterface)
						{
							ObjectPacksackInterface->Execute_UnReMoveItem(Components[0],PackItmeStruct);
						}
					}
				}
			}
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, DragDropOperation);
}
