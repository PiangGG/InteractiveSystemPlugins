// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP_Packsack_List_Item.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Data/PackListType.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "StorageDataList.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UStorageDataList : public UUserWidget,public IUIPacksackInterface
{
	GENERATED_BODY()
public:

	UFUNCTION()
	virtual TArray<FPackItmeStruct> GetStorageDataList_Implementation() override;

	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void UpdataUIData_Implementation(TArray<FPackItmeStruct>& StorageDataList) override;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	class UListView *GetListView();
public:
	/**
	 * List
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UNamedSlot* NamedSlot;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName = "列表类型"))
	EPackListType ListType = EPackListType::Tile;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UPackListView*PackListView;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UPackTileView*PackTileView;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UWBP_Packsack_List_Item> ListItem;

private:
	UPROPERTY()
	AActor* theOwner;

	
};
