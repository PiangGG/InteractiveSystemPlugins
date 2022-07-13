// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "InteractiveSystemPlugins/Data/PackItemData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InteractiveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UInteractiveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UInteractiveSubsystem();

	FPackItmeDataStruct* GetStructData(const FPackItmeStruct& packItmeStruct);

private:
	UPROPERTY()
	UDataTable* DT;
};
