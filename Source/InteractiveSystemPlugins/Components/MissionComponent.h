// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveSystemPlugins/Data/MissionStruct.h"
#include "MissionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEMPLUGINS_API UMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMissionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitMissData();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere,Category="Data",meta=(DisplayName="已接任务"))
	TArray<FName> MissionArray;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data",meta=(DisplayName="任务表格"))
	class UDataTable* MissionDataTable;
};
