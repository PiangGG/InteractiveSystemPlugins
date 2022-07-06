// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorPacksackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorPacksackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIVESYSTEMPLUGINS_API IActorPacksackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Pack(AController* Controller);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void TipActor(AController* Controller,bool bTip,int Value);
	/*UFUNCTION(BlueprintNativeEvent)
	AActor* Pack();*/
};
