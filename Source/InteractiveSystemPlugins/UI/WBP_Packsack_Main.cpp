// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Packsack_Main.h"

#include "Components/ListView.h"
#include "Components/SpinBox.h"
#include "InteractiveSystemPlugins/Object/Packsack_List_Item_Object.h"

bool UWBP_Packsack_Main::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	return true;
}

void UWBP_Packsack_Main::NativeConstruct()
{
	Super::NativeConstruct();

	if (RemoveItemBox)
	{
		RemoveItemBox->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (!GetWidgetOwner_Implementation())return;

	if (RemoveItemBox)
	{
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(RemoveItemBox);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->SetWidgetOwner(GetWidgetOwner_Implementation());
			UIPacksackInterface->Execute_SetParentWidget(this);
		}
	}
	
	if (StorageDataList)
	{
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(StorageDataList);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->SetWidgetOwner(GetWidgetOwner_Implementation());
			UIPacksackInterface->Execute_SetParentWidget(this);
		}
	}

	if (RemoveBox)
	{
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(RemoveBox);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->SetWidgetOwner(GetWidgetOwner_Implementation());
			UIPacksackInterface->Execute_SetParentWidget(this);
		}
	}
}

void UWBP_Packsack_Main::AddItem(UObject* Object)
{
	if (!GetListView()||!Object)return;
}

UListView* UWBP_Packsack_Main::GetListView()
{
	if (StorageDataList)
	{
		return StorageDataList->GetListView();
	}
	return nullptr;
}

void UWBP_Packsack_Main::UpdataUI_Implementation(UPacksackComponent* PacksackComponent)
{
	if (!GetListView()||!PacksackComponent)return;

	if (StorageDataList)
	{
		IUIPacksackInterface*UIPacksackInterface = CastChecked<IUIPacksackInterface>(StorageDataList);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->Execute_UpdataUIData(StorageDataList,PacksackComponent->PackDataList);
		}
	}
}

TArray<FPackItmeStruct> UWBP_Packsack_Main::GetStorageDataList_Implementation()
{
	if (true)
	{
		
	}
	return IUIPacksackInterface::GetStorageDataList_Implementation();
}

AActor* UWBP_Packsack_Main::GetWidgetOwner_Implementation()
{
	
	return IUIPacksackInterface::GetWidgetOwner_Implementation();
}

void UWBP_Packsack_Main::ShowRemoveItemBox(UPacksackComponent*PacksackComponent,const FPackItmeStruct& packItmeStruct)
{
	if (RemoveItemBox)
	{
		if (RemoveItemBox->SpinBox)
		{
			RemoveItemBox->SpinBox->SetValue(1.0f);
		}
		RemoveItemBox->SetParent(this);
		RemoveItemBox->PackItmeStruct = packItmeStruct;
		RemoveItemBox->SetVisibility(ESlateVisibility::Visible);
		PacksackComponent->SelectedOption.BindUFunction(PacksackComponent,FName("UnPickOptionSeleted"));
	}
}

void UWBP_Packsack_Main::HideRemoveItemBox(UPacksackComponent* PacksackComponent)
{
	if (RemoveItemBox)
	{
		RemoveItemBox->SetVisibility(ESlateVisibility::Hidden);
	}
}
