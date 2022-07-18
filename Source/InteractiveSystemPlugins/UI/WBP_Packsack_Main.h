// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StorageDataList.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
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
	
	/**
	 * 移除背包Item选择数量
	 */
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UWBP_Pack_RemoveItem_Box> RemoveItemBox_Sub;*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UWBP_Pack_RemoveItem_Box*RemoveItemBox;
	
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UStorageDataList> StorageDataList_Sub;*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UStorageDataList*StorageDataList;

	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UWBP_Pack_RemoveBox> RemoveBox_Sub;*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UWBP_Pack_RemoveBox*RemoveBox;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UStorage_List*StorageList;
	//TArray<UStorageDataList>&UStorageDataArray;
	
private:
	UPROPERTY()
	AActor*WidgetOnwenr;
public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	
	UFUNCTION(BlueprintCallable)
	void AddItem(UObject *Object);

	UFUNCTION(BlueprintCallable)
	class UListView *GetListView();
	
	UFUNCTION()
	virtual void UpdataUI_Implementation(UPacksackComponent* PacksackComponent) override;

	virtual TArray<FPackItmeStruct> GetStorageDataList_Implementation() override;
	
	UFUNCTION()
	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void SetWidgetOwner_Implementation(AActor* actor) override;
	UPROPERTY()
	APlayerController* PlayerController;

	void ShowRemoveItemBox(UPacksackComponent*PacksackComponent, const FPackItmeStruct& packItmeStruct);
	
	void HideRemoveItemBox(UPacksackComponent*PacksackComponent);

	void  MainClose();
};
