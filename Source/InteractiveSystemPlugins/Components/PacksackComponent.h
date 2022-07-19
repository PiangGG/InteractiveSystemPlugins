// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "InteractiveSystemPlugins/Interface/ObjectPacksackInterface.h"
#include "Net/UnrealNetwork.h"
#include "PacksackComponent.generated.h"


/*#define ETraceTypeQuery::TraceTypeQuery1 PackTraceSphere
#define ETraceTypeQuery::TraceTypeQuery2 PackTraceLine*/


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePackUI);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSelectedOption,bool,bSelectedOption,const FPackItmeStruct&,packItmeStruct);
class UWBP_Packsack_Main;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEMPLUGINS_API UPacksackComponent : public UActorComponent,public IObjectPacksackInterface
{
	GENERATED_BODY()

public:	
	
	UPacksackComponent();

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
	void UnPickShowSelected(const FPackItmeStruct& packItmeStruct);

	UFUNCTION()
	void UnPick(const FPackItmeStruct& packItmeStruct);

	UFUNCTION()
	void UnPickOptionSeleted(bool OptionSeleted,FPackItmeStruct& packItmeStruct);
	
	UFUNCTION(Server,WithValidation,Reliable)
	void UnPick_Server(const FPackItmeStruct& packItmeStruct);
	
	UFUNCTION()
	void ThrowOut(const FPackItmeStruct &packItmeStruct);
	UFUNCTION(Server,WithValidation,Reliable)
	void ThrowOut_Server(const FPackItmeStruct &packItmeStruct);
	
	UFUNCTION()
	void Picks(const FPackItmeStruct& packItmeStruct);
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
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<AActor*>& GetOverlapStorageBox();

	virtual TArray<FPackItmeStruct> GetDatas_Implementation() override;

	virtual void UpdataData_Implementation(int Index) override;

	virtual void ReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct) override;

	virtual void AddItem_Implementation(const FPackItmeStruct& packItmeStruct) override;


	virtual void UnReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct) override;
public:	
	
	
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	TArray<FPackItmeStruct> PackDataList;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UWBP_Packsack_Main> WBP_Packsack_Main;
	
	FDelegateHandle DelegateHandle;

	UPROPERTY()
	FUpdatePackUI UpdatePackUI;

	FDelegateHandle DelegateHandle_SelectedOption;
	
	UPROPERTY()
	FSelectedOption SelectedOption;

	UPROPERTY()
	AActor* LastTargetPackActor;

	UPROPERTY()
	AActor* CurrentTargetPackActor;
	
	TSharedPtr<FPackItmeStruct> PackItmeStruct;
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

	UPROPERTY()
	TArray<AActor*> OverlapStorageBox;
};


