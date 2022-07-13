// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "WBP_Pack_RemoveBox.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UWBP_Pack_RemoveBox : public UUserWidget,public IUIPacksackInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UOverlay*Overlay;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UImage * Image_bg;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UTextBlock* TextBlock;
public:

	virtual void NativeConstruct() override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void SetWidgetOwner_Implementation(AActor* actor) override;

	virtual UUserWidget* GetParentWidget_Implementation() override;
	
	virtual void SetParentWidget_Implementation(UUserWidget* parent) override;
private:
	UPROPERTY()
	AActor* Owner;
	UPROPERTY()
	UUserWidget* Parent;
};
