// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PacksackComponent.generated.h"


/*#define ETraceTypeQuery::TraceTypeQuery1 PackTraceSphere
#define ETraceTypeQuery::TraceTypeQuery2 PackTraceLine*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEMPLUGINS_API UPacksackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPacksackComponent();
	
	void PostInitProperties() override;
	
	//实例化背包数据
	void InitPacksackData(TArray<struct FPackItmeStruct*> &PackDataArray);

	//实例化碰撞组件
	void InitSphereComponent();
	
	UFUNCTION(BlueprintCallable)
	virtual TArray<class AActor*> GetAllOverlapActors();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	void Pick();
	/*
	 * 拥有者是否为Pawn
	 */
	bool GetOwberisPawn();

	UFUNCTION()
	void OnSphereComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereComponentEndOverlap(UPrimitiveComponent*OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UPROPERTY(Replicated)
	TArray<FPackItmeStruct*> PackDataList;

private:
	
	
	UPROPERTY()
	class USphereComponent* SphereComponent;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	TArray<AActor*> OutOverlappingActors;
};
