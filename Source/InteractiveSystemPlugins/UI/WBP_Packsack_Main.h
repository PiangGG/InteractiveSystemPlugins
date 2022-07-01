// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "WBP_Packsack_Main.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UWBP_Packsack_Main : public UUserWidget ,public IUIPacksackInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel*CanvasPanel_Main;

public:
	virtual bool Initialize() override;

	virtual void UpdataUI_Implementation();
};
