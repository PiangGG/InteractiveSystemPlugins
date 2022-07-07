// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Packsack_Main.h"

#include "PackListView.h"
#include "PackTileView.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ListView.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "Components/SpinBox.h"
#include "InteractiveSystemPlugins/Object/Packsack_List_Item_Object.h"

bool UWBP_Packsack_Main::Initialize()
{
	/*if (ListView_1)
	{
		switch (ListType)
		{
		case EPackListType::List:
			ListView_1 = PackListView;
			if (CastChecked<UPackListView>(ListView_1))
			{
				CastChecked<UPackListView>(ListView_1)->SetWidgetEntry(ListItem);
			}
			break;
		case EPackListType::Tile:
			ListView_1 = PackTileView;
			if (CastChecked<UPackTileView>(ListView_1))
			{
				CastChecked<UPackTileView>(ListView_1)->SetWidgetEntry(ListItem);
			}
			break;
		default:
			break;;
		}
	}*/
	if (CanvasPanel_Main)
	{
		CanvasPanel_Main->AddChildToCanvas(NamedSlot);
		CanvasPanel_Main->AddChildToCanvas(SizeBox);
	}
	if (SizeBox)
	{
		SizeBox->SetHeightOverride(HeightOverride);
		SizeBox->SetWidthOverride(WidthOverride);
	}
	if (NamedSlot)
	{
		NamedSlot->ClearChildren();
		//CastChecked<UCanvasPanelSlot>(SizeBox->Slot)->SetPosition(ListPosition);
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
	if (!Super::Initialize())
	{
		return false;
	}
	return true;
}

void UWBP_Packsack_Main::NativeConstruct()
{
	Super::NativeConstruct();
	
	//RemoveItem_Box = CreateWidget<UWBP_Pack_RemoveItem_Box>(CastChecked<APlayerController>(GetGameInstance()->GetFirstLocalPlayerController()),WBP_Pack_RemoveItem_Box);
	if (RemoveItem_Box)
	{
		RemoveItem_Box->SetVisibility(ESlateVisibility::Hidden);
	}
}

UListView* UWBP_Packsack_Main::GetListView()
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

void UWBP_Packsack_Main::AddItem(UObject* Object)
{
	if (!GetListView()||!Object)return;
}

void UWBP_Packsack_Main::UpdataUI_Implementation(UPacksackComponent* PacksackComponent)
{
	if (!GetListView()||!PacksackComponent)return;
	GetListView()->ClearListItems();
	GetListView()->ClearSelection();
	for (auto PackDataItme : PacksackComponent->PackDataList)
	{
		UPacksack_List_Item_Object *Object = NewObject<UPacksack_List_Item_Object>();
		Object->SetPackItme(PackDataItme);
		GetListView()->AddItem(Object);
	}
}

void UWBP_Packsack_Main::ShowRemoveItemBox(UPacksackComponent*PacksackComponent,const FPackItmeStruct& packItmeStruct)
{
		if (RemoveItem_Box)
		{
			if (RemoveItem_Box->SpinBox)
			{
				RemoveItem_Box->SpinBox->SetValue(1.0f);
			}
			RemoveItem_Box->SetParent(this);
			RemoveItem_Box->PackItmeStruct = packItmeStruct;
			RemoveItem_Box->SetVisibility(ESlateVisibility::Visible);
			PacksackComponent->SelectedOption.BindUFunction(PacksackComponent,FName("UnPickOptionSeleted"));
		}
}

void UWBP_Packsack_Main::HideRemoveItemBox(UPacksackComponent* PacksackComponent)
{
	if (RemoveItem_Box)
	{
		RemoveItem_Box->SetVisibility(ESlateVisibility::Hidden);
	}
}
