// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageComponent.h"

#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "InteractiveSystemPlugins/UI/StorageDataList.h"
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
	
	//StorageDataList = CreateWidget<UStorageDataList>(GetOwner(),StorageDataList_Sub);
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

UStorageDataList* UStorageComponent::GetStorageDatasWBP(APlayerController* PlayerController)
{
	if (!StorageDataList)
	{
		StorageDataList = CreateWidget<UStorageDataList>(PlayerController,StorageDataList_Sub);
		if (CastChecked<IUIPacksackInterface>(StorageDataList))
		{
			CastChecked<IUIPacksackInterface>(StorageDataList)->Execute_SetWidgetOwner(StorageDataList,GetOwner());
		}
	}
	return StorageDataList;
}

void UStorageComponent::UpdataStorageDatasWBP(APlayerController* PlayerController)
{
	/*if (!GetStorageDatasWBP(CastChecked<APlayerController>(PlayerController)))return;
	
	IUIPacksackInterface* UIPacksackInterface = CastChecked<IUIPacksackInterface>(GetStorageDatasWBP(CastChecked<APlayerController>(PlayerController)));
	
	if (UIPacksackInterface)
	{
		UIPacksackInterface->Execute_UpdataUIData(StorageDataList,Data);
	}*/
}

void UStorageComponent::AddDataItem(FPackItmeStruct& Item)
{
	
}

void UStorageComponent::ReMoveDataItem(FPackItmeStruct& Item)
{
	
}

