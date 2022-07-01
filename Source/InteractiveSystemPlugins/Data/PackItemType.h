// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPackItemType :uint8
{
	Base		UMETA(DisplayName = "基础"),
	Weapon		UMETA(DisplayName = "武器")
};