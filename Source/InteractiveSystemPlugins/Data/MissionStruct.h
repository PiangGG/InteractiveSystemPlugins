// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackItem.h"
#include "Engine/DataTable.h"
#include "MissionStruct.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FMissionStruct:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务名称"))
	FName Name = "NewMission";

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务图标"))
	UTexture2D *Icon;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务介绍"))
	FString Introduce;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务描述"))
	FString Describe;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务条件"))
	TArray<FPackItmeStruct> MissionNeedData;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="任务奖励"))
	TArray<FPackItmeStruct> MissionReward;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Mission",meta=(DisplayName="当前任务子任务名称列表"))
	TArray<FName> SubMissionNames;
};