// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Components/PacksackComponent.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "UObject/Interface.h"
#include "UIPacksackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUIPacksackInterface : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class INTERACTIVESYSTEMPLUGINS_API IUIPacksackInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void UpdataUI(UPacksackComponent* PacksackComponent);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FPackItmeStruct GetPackItmeStruct();
};
