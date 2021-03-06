// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "WBP_Packsack_List_Item.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UWBP_Packsack_List_Item : public UUserWidget,public IUIPacksackInterface,public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	
	virtual void PostInitProperties() override;

	
	virtual void UpdataUI_Implementation(UPacksackComponent* PacksackComponent) override;

	virtual void NativeConstruct() override;

	virtual FPackItmeStruct GetPackItmeStruct_Implementation() override;

	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void SetWidgetOwner_Implementation(AActor* actor) override;

	virtual void SetParentWidget_Implementation(UUserWidget* parent) override;

	virtual UUserWidget* GetParentWidget_Implementation() override;
	/**
	 * 拖拽UI事件
	 */
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere,Category="Data")
	FPackItmeStruct PackItmeStruct;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Object")
	class UPacksack_List_Item_Object * Object;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class USizeBox*SizeBox;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class UOverlay*Overlay;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class UImage *Image_Bg;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class UImage *Image_Icon;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class UTextBlock *Name;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="WBP",meta=(BindWidget))
	class UTextBlock *Number;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Data",meta=(BindWidget))
	float Width = 100.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Data",meta=(BindWidget))
	float Height = 100.0f;

private:
	UPROPERTY()
	AActor*Owner;

	UPROPERTY()
	UUserWidget* Parent;
};
