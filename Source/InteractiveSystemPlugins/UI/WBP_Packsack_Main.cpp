// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Packsack_Main.h"

#include "Storage_List.h"
#include "WBP_Pack_RemoveBox.h"
#include "WBP_Pack_RemoveItem_Box.h"
#include "Components/ListView.h"
#include "Components/SpinBox.h"

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

	if (!WidgetOnwenr)return;
	
	if (RemoveItemBox)
	{
		RemoveItemBox->SetVisibility(ESlateVisibility::Hidden);
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(RemoveItemBox);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->Execute_SetWidgetOwner(RemoveItemBox,WidgetOnwenr);
			UIPacksackInterface->Execute_SetParentWidget(RemoveItemBox,this);
		}
	}
	
	if (StorageDataList)
	{
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(StorageDataList);
		if (UIPacksackInterface)
		{
			
			AActor* Actor = UIPacksackInterface->Execute_GetWidgetOwner(this);
			
			UIPacksackInterface->Execute_SetWidgetOwner(StorageDataList,WidgetOnwenr);
			UIPacksackInterface->Execute_SetParentWidget(StorageDataList,this);
		}
	}

	if (RemoveBox)
	{
		IUIPacksackInterface *UIPacksackInterface = CastChecked<IUIPacksackInterface>(RemoveBox);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->Execute_SetWidgetOwner(RemoveBox,WidgetOnwenr);
			UIPacksackInterface->Execute_SetParentWidget(RemoveBox,this);
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
	if (StorageList)
	{
		IUIPacksackInterface*UIPacksackInterface = CastChecked<IUIPacksackInterface>(StorageList);
		if (UIPacksackInterface)
		{
			UIPacksackInterface->Execute_UpdataStorageListData(StorageList,PacksackComponent->GetOverlapStorageBox());
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
	if (WidgetOnwenr)
	{
		return WidgetOnwenr;
	}
	return IUIPacksackInterface::GetWidgetOwner_Implementation();
}

void UWBP_Packsack_Main::SetWidgetOwner_Implementation(AActor* actor)
{
	IUIPacksackInterface::SetWidgetOwner_Implementation(actor);
	WidgetOnwenr = actor;
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
