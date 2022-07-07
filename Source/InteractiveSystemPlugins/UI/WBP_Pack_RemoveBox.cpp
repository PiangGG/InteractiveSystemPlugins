// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Pack_RemoveBox.h"

#include "WBP_Packsack_List_Item.h"
#include "Blueprint/DragDropOperation.h"
#include "InteractiveSystemPlugins/Object/PackItemDragDropOperation.h"

bool UWBP_Pack_RemoveBox::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{
	UPackItemDragDropOperation *DragDropOperation = Cast<UPackItemDragDropOperation>(InOperation);
	if (InOperation)
	{
		UWBP_Packsack_List_Item* DragShowUI =CastChecked<UWBP_Packsack_List_Item>(InOperation->Payload);
		if (DragShowUI)
		{
			if (GetWorld()->GetFirstPlayerController()&&GetWorld()->GetFirstPlayerController()->GetPawn())
			{
				GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass());
				if (GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()))
				{
					if (CastChecked<UPacksackComponent>(GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass())))
					{
						APawn *Pawn = GetGameInstance()->GetFirstLocalPlayerController()->GetPawn();
						if (Pawn)
						{
							IUIPacksackInterface *UIPacksackInterface = Cast<IUIPacksackInterface>(DragShowUI);
							if (UIPacksackInterface)
							{
								
								if (CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass())))
								{
									UPacksackComponent * PacksackComponent= CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass()));
									if (PacksackComponent)
									{
										FPackItmeStruct PackItmeStruct =  UIPacksackInterface->Execute_GetPackItmeStruct(DragShowUI);
										PacksackComponent->UnPickShowSelected(PackItmeStruct);
									}
								}
							}
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
}
