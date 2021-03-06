// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PackItem.generated.h"
/**
 * 
 */
class AItem;
USTRUCT(BlueprintType)
struct FPackItmeStruct:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="保存类"))
	TSubclassOf<class AItem> ItemClass;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="数量"))
	int Numbers = 1;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="命名"))
	FName Name = "Cube";

	FPackItmeStruct()
	{
		ItemClass = AActor::StaticClass();
		Numbers = 1;
		Name = "Cube";
	}
	FPackItmeStruct(TSubclassOf<AItem> Class)
	{
		ItemClass = Class;
		Numbers = 1;
		Name = "NewKey";
	}
	FPackItmeStruct(TSubclassOf<AItem> Class,FName name)
	{
		ItemClass = Class;
		Numbers = 1;
		Name = name;
		
	}
	FPackItmeStruct(TSubclassOf<AItem> Class,int numbers,FName name)
	{
		ItemClass = Class;
		Numbers = numbers;
		Name = name;
	}

	FPackItmeStruct(const FPackItmeStruct& PackItmeStruct)
	{
		ItemClass = PackItmeStruct.ItemClass;
		Numbers = PackItmeStruct.Numbers;
		Name = PackItmeStruct.Name;
	}
};