// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "PackTileView.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UPackTileView : public UTileView
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetWidgetEntry(TSubclassOf<UUserWidget> EntryWidget);
};
