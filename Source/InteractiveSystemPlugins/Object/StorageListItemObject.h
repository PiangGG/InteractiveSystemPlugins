// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Interface/ObjectPacksackInterface.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "UObject/NoExportTypes.h"
#include "StorageListItemObject.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UStorageListItemObject : public UObject,public IObjectPacksackInterface,public IUIPacksackInterface
{
	GENERATED_BODY()
private:
	
	UPROPERTY()
	AActor * StorageActor;
	
	UPROPERTY()
	UUserWidget* userwidget;
public:
	
	UFUNCTION(BlueprintCallable)
	void SetStorageActor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	AActor *GetStorageActor();

	virtual TArray<FPackItmeStruct> GetObjectDatas_Implementation(UObject* Object) override;

	UFUNCTION(BlueprintCallable)
	TArray<FPackItmeStruct>& GetObjectDatasbyRef();

	virtual void SetEntryWidget_Implementation(UUserWidget* UserWidget) override;

	virtual UUserWidget* GetEntryWidget_Implementation() override;

	virtual void SetWidgetOwner_Implementation(AActor* actor) override;

	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void SetParentWidget_Implementation(UUserWidget* parent) override;

	virtual UUserWidget* GetParentWidget_Implementation() override;

	virtual FPackItmeStruct GetPackItmeStruct_Implementation() override;
};
