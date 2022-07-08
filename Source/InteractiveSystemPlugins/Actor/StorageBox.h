// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "StorageBox.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API AStorageBox : public AItem
{
	GENERATED_BODY()

public:
	AStorageBox();
	

protected:
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStorageComponent* StorageComponent;

public:
	virtual void Pack_Implementation(AController* Controller) override;
};
