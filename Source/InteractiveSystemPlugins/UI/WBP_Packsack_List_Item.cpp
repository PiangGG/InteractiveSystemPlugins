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
	/*Object = GetListItem<UPacksack_List_Item_Object>();
	if (!Object)return;
	
	PackItmeStruct = Object->PackItme;
	auto Item= Cast<AItem>(PackItmeStruct.ItemClass);
	Image_Bg->SetToolTipText(FText::FromString(Item->Data->Describe));*/
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

AActor* UWBP_Packsack_List_Item::GetWidgetOwner_Implementation()
{
	if (Owner)
	{
		return Owner;
	}
	return IUIPacksackInterface::GetWidgetOwner_Implementation();
}

void UWBP_Packsack_List_Item::SetWidgetOwner_Implementation(AActor* actor)
{
	IUIPacksackInterface::SetWidgetOwner_Implementation(actor);
	
	Owner = actor;
}

void UWBP_Packsack_List_Item::SetParentWidget_Implementation(UUserWidget* parent)
{
	IUIPacksackInterface::SetParentWidget_Implementation(parent);
	Parent = parent;
}

UUserWidget* UWBP_Packsack_List_Item::GetParentWidget_Implementation()
{
	if (Parent)
	{
		return Parent;
	}
	return IUIPacksackInterface::GetParentWidget_Implementation();
}


FReply UWBP_Packsack_List_Item::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
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

			IUIPacksackInterface* UIPacksackInterface = Cast<IUIPacksackInterface>(DragShowUI);
			if (UIPacksackInterface)
			{
				UIPacksackInterface->Execute_SetWidgetOwner(DragShowUI,IPacksackInterface->Execute_GetWidgetOwner(this));
				UIPacksackInterface->Execute_SetParentWidget(DragShowUI,IPacksackInterface->Execute_GetParentWidget(this));
			}
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
		
		IUIPacksackInterface* IPacksackInterface1 = Cast<IUIPacksackInterface>(DragShowUI);
		if (IPacksackInterface1)
		{
			AActor * Actor = IPacksackInterface1->Execute_GetWidgetOwner(DragShowUI);

			if (Actor)
			{
				TArray<UActorComponent*>Components = Actor->GetComponentsByInterface(UObjectPacksackInterface::StaticClass());
		
				if (Components.IsValidIndex(0))
				{
					IObjectPacksackInterface*ObjectPacksackInterface = CastChecked<IObjectPacksackInterface>(Components[0]);
					if (ObjectPacksackInterface)
					{
						for (int i = 0;i< ObjectPacksackInterface->Execute_GetDatas(Components[0]).Num();i++)
						{
							if (ObjectPacksackInterface->Execute_GetDatas(Components[0])[i].Name == PackItmeStruct.Name && ObjectPacksackInterface->Execute_GetDatas(Components[0]).IsValidIndex(i))
							{
								//ObjectPacksackInterface->Execute_GetDatas(Components[0]).RemoveAt(i);
								ObjectPacksackInterface->Execute_UpdataData(Components[0],i);
								return ;
							}
						}
					}
				}
			}
		}
	}
}


bool UWBP_Packsack_List_Item::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	//return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}

void UWBP_Packsack_List_Item::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}


void UWBP_Packsack_List_Item::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
                                                    UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	
	/*UPackItemDragDropOperation *DragDropOperation = Cast<UPackItemDragDropOperation>(InOperation);
	
	if (InOperation&&DragDropOperation)
	{
		UWBP_Packsack_List_Item* DragShowUI =CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload);
		if (DragShowUI)
		{
			IUIPacksackInterface * UIPacksackInterface = CastChecked<IUIPacksackInterface>(DragShowUI);
			
			if (UIPacksackInterface&&Owner&&Parent)
			{
				UIPacksackInterface->Execute_SetWidgetOwner(DragShowUI,Owner);
				
				UIPacksackInterface->Execute_SetParentWidget(DragShowUI,Parent);

				AActor*Actor = UIPacksackInterface->Execute_GetWidgetOwner(DragShowUI);

				if (Actor)
				{
					TArray<UActorComponent*>Components = Actor->GetComponentsByInterface(UObjectPacksackInterface::StaticClass());
		
					if (Components.IsValidIndex(0))
					{
						IObjectPacksackInterface*ObjectPacksackInterface = CastChecked<IObjectPacksackInterface>(Components[0]);
						
						if (ObjectPacksackInterface)
						{
							ObjectPacksackInterface->Execute_UnReMoveItem(Components[0],DragShowUI->PackItmeStruct);
						}
					}
				}
			}
		}
	}*/
}


void UWBP_Packsack_List_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UWBP_Packsack_List_Item,PackItmeStruct);
}
