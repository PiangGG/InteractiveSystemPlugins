// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Pack_RemoveItem_Box.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "InteractiveSystemPlugins/Components/PacksackComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UWBP_Pack_RemoveItem_Box::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_true)
	{
		Button_true->SetStyle(ButtonStyle);
		Button_true->OnClicked.AddDynamic(this,&ThisClass::OnClickTrue);
	}
	if (Button_false)
	{
		Button_false->SetStyle(ButtonStyle);
		Button_false->OnClicked.AddDynamic(this,&ThisClass::OnClickFalse);
	}
	/*if (SizeBox&&Image_Bg&&Overlay)
	{
		
		SizeBox->AddChild(Overlay);
		Overlay->AddChildToOverlay(Image_Bg);
	}

	if (TextBlock_Show)
	{
		TextBlock_Show->SetText(FText::FromString("请选择丢弃数量"));
	}
	if (TextBlock_Ture)
	{
		TextBlock_Ture->SetText(FText::FromString("确定"));
	}
	if (TextBlock_False)
	{
		TextBlock_False->SetText(FText::FromString("取消"));
	}*/
}

void UWBP_Pack_RemoveItem_Box::SetParent(UUserWidget* parent)
{
	Parent = parent;
}

void UWBP_Pack_RemoveItem_Box::OnClickTrue()
{
	UE_LOG(LogTemp,Warning,TEXT("OnClickTrue"));
	OnClickOption = true;
	if (SpinBox)
	{
		RemoveNumber = UKismetMathLibrary::Conv_DoubleToInt64(SpinBox->GetValue());
	}
	APawn *Pawn = GetGameInstance()->GetFirstLocalPlayerController()->GetPawn();
	if (Pawn)
	{
		if (CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass())))
		{
			UPacksackComponent * PacksackComponent= CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass()));
			if (PacksackComponent)
			{
				PacksackComponent->SelectedOption.ExecuteIfBound(OnClickOption,packItmeStruct);
			}
		}
		
	}
}

void UWBP_Pack_RemoveItem_Box::OnClickFalse()
{
	UE_LOG(LogTemp,Warning,TEXT("OnClickFalse"));
	OnClickOption = false;
	APawn *Pawn = GetGameInstance()->GetFirstLocalPlayerController()->GetPawn();
	if (Pawn)
	{
		if (CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass())))
		{
			UPacksackComponent * PacksackComponent= CastChecked<UPacksackComponent>(Pawn->GetComponentByClass(UPacksackComponent::StaticClass()));
			if (PacksackComponent)
			{
				PacksackComponent->SelectedOption.ExecuteIfBound(OnClickOption,packItmeStruct);
			}
		}
		
	}
}
