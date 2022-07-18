// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Pack_RemoveBox.h"

#include "WBP_Packsack_List_Item.h"
#include "Blueprint/DragDropOperation.h"
#include "InteractiveSystemPlugins/Object/PackItemDragDropOperation.h"

void UWBP_Pack_RemoveBox::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TextBlock)
	{
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UWBP_Pack_RemoveBox::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{
	if (TextBlock)
	{
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	
	UPackItemDragDropOperation *DragDropOperation = Cast<UPackItemDragDropOperation>(InOperation);
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
							ObjectPacksackInterface->Execute_ReMoveItem(Components[0],DragShowUI->PackItmeStruct);
						}
					}
				}
			}
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, DragDropOperation);
}

void UWBP_Pack_RemoveBox::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	if (TextBlock)
	{
		TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UWBP_Pack_RemoveBox::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	if (TextBlock)
	{
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
}

AActor* UWBP_Pack_RemoveBox::GetWidgetOwner_Implementation()
{
	if (Owner)
	{
		return Owner;
	}
	return IUIPacksackInterface::GetWidgetOwner_Implementation();
}

void UWBP_Pack_RemoveBox::SetWidgetOwner_Implementation(AActor* actor)
{
	IUIPacksackInterface::SetWidgetOwner_Implementation(actor);
	Owner = actor;
}

UUserWidget* UWBP_Pack_RemoveBox::GetParentWidget_Implementation()
{
	if (Parent)
	{
		return Parent;
	}
	return IUIPacksackInterface::GetParentWidget_Implementation();
}

void UWBP_Pack_RemoveBox::SetParentWidget_Implementation(UUserWidget* parent)
{
	IUIPacksackInterface::SetParentWidget_Implementation(parent);
	
	Parent = parent;
}
