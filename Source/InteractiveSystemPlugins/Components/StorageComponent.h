// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "InteractiveSystemPlugins/Interface/ObjectPacksackInterface.h"
#include "StorageComponent.generated.h"


class UStorageDataList;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEMPLUGINS_API UStorageComponent : public UActorComponent,public IObjectPacksackInterface
{
	GENERATED_BODY()

public:	
	UStorageComponent();

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void InitData(TArray<FPackItmeStruct>& ata);

	UStorageDataList* GetStorageDatasWBP(APlayerController* PlayerController);

	void  UpdataStorageDatasWBP(APlayerController* PlayerController);

	virtual TArray<FPackItmeStruct> GetDatas_Implementation() override;

	UFUNCTION()
	void ThrowOut(const FPackItmeStruct &packItmeStruct);
	UFUNCTION(Server,WithValidation,Reliable)
	void ThrowOut_Server(const FPackItmeStruct &packItmeStruct);
	
	virtual void UpdataData_Implementation(int Index) override;

	virtual void ReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct) override;

	virtual void AddItem_Implementation(const FPackItmeStruct& packItmeStruct) override;
public:
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	TArray<FPackItmeStruct> Data;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> StorageDataList_Sub;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class UStorageDataList*StorageDataList;


};
