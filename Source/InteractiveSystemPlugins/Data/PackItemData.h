// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackItemType.h"
#include "Engine/DataTable.h"
#include "PackItemData.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FPackItmeDataStruct:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="名称"))
	FName Name;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="描述"))
	FString Describe;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="类型"))
	EPackItemType Type;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="静态模型"))
	UStaticMesh * Mesh_SM;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="骨骼模型"))
	USkeletalMesh * Mesh_SK;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="图标"))
	UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="碰撞体半径"))
	float SphereRadius = 32.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="模拟物理"))
	bool bSimulate = true;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="FPackItmeStruct",meta=(DisplayName="靠近显示UI"))
	TSubclassOf<UUserWidget> ShowUI;
};