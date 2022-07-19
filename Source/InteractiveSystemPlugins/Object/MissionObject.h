// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Data/MissionStruct.h"
#include "MissionObject.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UMissionObject : public UObject
{
	GENERATED_BODY()
	
public:
	FMissionStruct MissionStruct;
};
