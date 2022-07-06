// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "PackListView.generated.h"

/**
 * 继承自ListView 重载设置Widget
 */

UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UPackListView : public UListView
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetWidgetEntry(TSubclassOf<UUserWidget> EntryWidget);
};
