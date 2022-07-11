// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "Storage_List.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UStorage_List : public UUserWidget,public IUIPacksackInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UPackListView*StorageListView;

public:
	virtual bool Initialize() override;
	
	virtual void NativeConstruct() override;

	virtual void UpdataStorageListData_Implementation(TArray<AActor*> &StorageList) override;
	
};
