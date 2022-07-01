// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveSystemPlugins/Data/PackItemData.h"
#include "Item.generated.h"

UCLASS()
class INTERACTIVESYSTEMPLUGINS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

	virtual void Init();
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Show();
	UFUNCTION()
	virtual void Hide();
private:
	
	
public:
	/*
	 * 名字  数据驱动 从表中动态获取数据
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data",meta=(DisplayName="Item命名"))
	FString Name = "Cube";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data",meta=(DisplayName="Item列表"))
	UDataTable * DT;
	//UPROPERTY()
	FPackItmeDataStruct* Data;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Compment",meta=(DisplayName="Root"))
	class USceneComponent *SceneComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Compment",meta=(DisplayName="拾取碰撞"))
	class USphereComponent *SphereComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Compment",meta=(DisplayName="靠近显示UI"))
	class UWidgetComponent* WidgetComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Compment",meta=(DisplayName="靠近显示UI"))
	UUserWidget *ShowUI;
};

