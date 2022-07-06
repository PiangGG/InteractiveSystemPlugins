// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "PacksackComponent.generated.h"


/*#define ETraceTypeQuery::TraceTypeQuery1 PackTraceSphere
#define ETraceTypeQuery::TraceTypeQuery2 PackTraceLine*/


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePackUI);
class UWBP_Packsack_Main;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEMPLUGINS_API UPacksackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPacksackComponent();
	
	void PostInitProperties() override;
	
	//实例化背包数据
	void InitPacksackData(TArray<FPackItmeStruct> &PackDataArray);

	//实例化碰撞组件
	void InitSphereComponent();
	
	UFUNCTION(BlueprintCallable)
	virtual TArray<class AActor*> GetAllOverlapActors();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	void PickByF();
	UFUNCTION()
	void Pick();
	UFUNCTION(Server,Reliable)
	void PickServer();
	UFUNCTION(NetMulticast,Reliable)
	void PickNetMulticast();

	
public:
	UFUNCTION()
	void OpenPick();
	
	UFUNCTION(BlueprintCallable)
	void UpdatePick();
	UFUNCTION(Server,WithValidation,Reliable)
	void UpdatePick_Server();
	UFUNCTION(NetMulticast,Reliable)
	void UpdatePick_NetMulticast();
	UFUNCTION(BlueprintCallable)
	void UpdatePick_TimerBegin();
	UFUNCTION(BlueprintCallable)
	void UpdatePick_TimerEnd();

	UFUNCTION()
	void UnPick(FPackItmeStruct &packItmeStruct);

	UFUNCTION()
	void ThrowOut(FPackItmeStruct &packItmeStruct);
	
	/*
	 * 拥有者是否为Pawn
	 */
	bool GetOwberisPawn();

	UFUNCTION()
	void OnSphereComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereComponentEndOverlap(UPrimitiveComponent*OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginDestroy() override;

	UFUNCTION()
	void SetTargetPackActorTip();
	UPROPERTY()
	AActor* LastTargetPackActor;

	UPROPERTY()
	AActor* CurrentTargetPackActor;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	TArray<FPackItmeStruct> PackDataList;
	


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UWBP_Packsack_Main> WBP_Packsack_Main;

	FDelegateHandle DelegateHandle;
	
	FUpdatePackUI UpdatePackUI;
private:
	
	
	UPROPERTY()
	class USphereComponent* SphereComponent;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	TArray<AActor*> OutOverlappingActors;
	
	UPROPERTY()
	class UUserWidget* PackWidget;

	FTimerHandle TimerHandle_UpdatePack;
};
