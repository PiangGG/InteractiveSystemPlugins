// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "InteractiveSystemPlugins/Interface/ObjectPacksackInterface.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "Packsack_List_Item_Object.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UPacksack_List_Item_Object : public UObject,public IObjectPacksackInterface,public IUIPacksackInterface
{
	GENERATED_BODY()

public:
	
	UPacksack_List_Item_Object();
	
	UPacksack_List_Item_Object(FPackItmeStruct &PackItmeStruct);
	
	UPROPERTY(Replicated,EditAnywhere,BlueprintReadWrite)
	FPackItmeStruct PackItme;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable)
	void SetPackItme(FPackItmeStruct &PackItmeStruct);
	
	void SetPackItmeData(FPackItmeStruct PackItmeStruct);
	
	UFUNCTION(BlueprintCallable)
	virtual FPackItmeStruct GetObjectData_Implementation(UObject* Object) override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetParent();
	UFUNCTION(BlueprintCallable)
	void SetParent(UUserWidget *parent);

	virtual void SetWidgetOwner_Implementation(AActor* actor) override;

	virtual AActor* GetWidgetOwner_Implementation() override;

	virtual void SetParentWidget_Implementation(UUserWidget* parent) override;

	virtual UUserWidget* GetParentWidget_Implementation() override;

	virtual FPackItmeStruct GetPackItmeStruct_Implementation() override;
private:
	UPROPERTY()
	AActor *OwnerActor;
	
	UPROPERTY()
	class UUserWidget* Parent;
};
