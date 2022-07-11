// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "UObject/Interface.h"
#include "ObjectPacksackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectPacksackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIVESYSTEMPLUGINS_API IObjectPacksackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FPackItmeStruct GetObjectData(UObject*Object);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FPackItmeStruct> GetObjectDatas(UObject*Object);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetEntryWidget(UUserWidget* UserWidget);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UUserWidget* GetEntryWidget();

};
