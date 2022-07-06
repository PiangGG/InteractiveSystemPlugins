// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP_Packsack_List_Item.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "InteractiveSystemPlugins/Data/PackListType.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "WBP_Packsack_Main.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UWBP_Packsack_Main : public UUserWidget,public IUIPacksackInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UCanvasPanel*CanvasPanel_Main;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UNamedSlot* NamedSlot;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UWBP_Pack_RemoveBox*RemoveBox;
	/*
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UListView * ListView_1;
	*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UPackListView*PackListView;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UPackTileView*PackTileView;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class USizeBox*SizeBox;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UWBP_Packsack_List_Item> ListItem;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D ListPosition = FVector2D(0.0f,0.0f);
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float WidthOverride = 500.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float HeightOverride = 500.0f;
private:
	
public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	class UListView *GetListView();

	UFUNCTION(BlueprintCallable)
	void AddItem(UObject *Object);
	
	UFUNCTION()
	virtual void UpdataUI_Implementation(UPacksackComponent* PacksackComponent) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName = "列表类型"))
	EPackListType ListType = EPackListType::Tile;

	UPROPERTY()
	APlayerController* PlayerController;
};
