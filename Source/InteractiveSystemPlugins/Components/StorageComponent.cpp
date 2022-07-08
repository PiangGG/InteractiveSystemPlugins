// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageComponent.h"

#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicated(true);
}


void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();


	
}

void UStorageComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	StorageDataList = CreateWidget<UStorageDataList>(GetOwner(),StorageDataList_Sub);
}

void UStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStorageComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UStorageComponent,Data);
}

void UStorageComponent::InitData(TArray<FPackItmeStruct>& data)
{
	Data = data;
}

