// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Packsack_List_Item.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "InteractiveSystemPlugins/Object/PackItemDragDropOperation.h"
#include "InteractiveSystemPlugins/Object/Packsack_List_Item_Object.h"
#include "Net/UnrealNetwork.h"

void UWBP_Packsack_List_Item::PostInitProperties()
{
	Super::PostInitProperties();

	OnInitialized();
	
}

void UWBP_Packsack_List_Item::UpdataUI_Implementation(UPacksackComponent* PacksackComponent)
{
	Object = GetListItem<UPacksack_List_Item_Object>();
	if (!Object)return;
	
	PackItmeStruct = Object->PackItme;
	auto Item= Cast<AItem>(PackItmeStruct.ItemClass);
	Image_Bg->SetToolTipText(FText::FromString(Item->Data->Describe));
}

void UWBP_Packsack_List_Item::OnCreationFromPalette()
{
	Super::OnCreationFromPalette();
	
}

void UWBP_Packsack_List_Item::NativeConstruct()
{
	Super::NativeConstruct();
	if (SizeBox)
	{
		SizeBox->SetHeightOverride(Height);
		SizeBox->SetWidthOverride(Width);
	}
	Object = GetListItem<UPacksack_List_Item_Object>();
	if (Object)
	{
		if (CastChecked<UPacksack_List_Item_Object>(Object))
		{
			PackItmeStruct = CastChecked<UPacksack_List_Item_Object>(Object)->PackItme;
		}
	}
	else
	{
		IUIPacksackInterface* IPacksackInterface = Cast<IUIPacksackInterface>(this);
		if (IPacksackInterface)
		{
			PackItmeStruct = IPacksackInterface->Execute_GetPackItmeStruct(this);
		}
	}
}

FPackItmeStruct UWBP_Packsack_List_Item::GetPackItmeStruct_Implementation()
{
	//UE_LOG(LogTemp,Warning,TEXT("GetPackItmeStruct_Implementation:%s"),PackItmeStruct.Name.ToString());
	return IUIPacksackInterface::GetPackItmeStruct_Implementation();
}


FReply UWBP_Packsack_List_Item::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	UE_LOG(LogTemp,Warning,TEXT("NativeOnMouseButtonDown"));
	
	if (InMouseEvent.GetEffectingButton()==EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(),EKeys::LeftMouseButton);
		return Reply;
	}
	return Reply;
}


void UWBP_Packsack_List_Item::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UE_LOG(LogTemp,Warning,TEXT("NativeOnDragDetected"));
	UWBP_Packsack_List_Item* DragShowUI = CreateWidget<UWBP_Packsack_List_Item>(GetWorld(),ThisClass::StaticClass());
	if (DragShowUI)
	{
		IUIPacksackInterface* IPacksackInterface = Cast<IUIPacksackInterface>(this);
		if (IPacksackInterface)
		{
			PackItmeStruct = IPacksackInterface->Execute_GetPackItmeStruct(this);
			DragShowUI->PackItmeStruct.Name = PackItmeStruct.Name;
			DragShowUI->PackItmeStruct.Numbers = PackItmeStruct.Numbers;
			DragShowUI->PackItmeStruct.ItemClass = PackItmeStruct.ItemClass;
		}
		else
		{
			DragShowUI->PackItmeStruct = PackItmeStruct;
		}
		DragShowUI->Image_Icon = Image_Icon;
		
		UPackItemDragDropOperation *DragDropOperation = NewObject<UPackItemDragDropOperation>(GetWorld(),UPackItemDragDropOperation::StaticClass());
		if (DragDropOperation)
		{
			DragDropOperation->Payload = this;
			DragDropOperation->DefaultDragVisual = this;
			DragDropOperation->Pivot = EDragPivot::CenterCenter;
			OutOperation = DragDropOperation;
			
		}
	}
	
}

bool UWBP_Packsack_List_Item::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                           UDragDropOperation* InOperation)
{
	if (InOperation->Payload)
	{
		UWBP_Packsack_List_Item* DragShowUI =CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload);
		if (DragShowUI)
		{
			//UE_LOG(LogTemp,Warning,TEXT("UWBP_Packsack_List_Item::NativeOnDrop"));
		}
		
	}
	//return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}

void UWBP_Packsack_List_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UWBP_Packsack_List_Item,PackItmeStruct);
}
