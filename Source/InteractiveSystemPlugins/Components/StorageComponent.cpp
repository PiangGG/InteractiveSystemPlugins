// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageComponent.h"

#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Actor/Item.h"
#include "InteractiveSystemPlugins/Interface/UIPacksackInterface.h"
#include "InteractiveSystemPlugins/UI/StorageDataList.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	//SetIsReplicated(true);
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

TArray<FPackItmeStruct> UStorageComponent::GetDatas_Implementation()
{
	return Data;
}

void UStorageComponent::ThrowOut(const FPackItmeStruct& packItmeStruct)
{
	ThrowOut_Server(packItmeStruct);
}

void UStorageComponent::ThrowOut_Server_Implementation(const FPackItmeStruct& packItmeStruct)
{
	if (GetOwner())
	{
		for (int i = 0;i<packItmeStruct.Numbers;i++)
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			auto* Item = GetWorld()->SpawnActor<AItem>(packItmeStruct.ItemClass,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation(),ActorSpawnParameters);

			if (Item)
			{
				Item->Name = packItmeStruct.Name.ToString();
				CastChecked<AItem>(Item)->Init(packItmeStruct.Name);
			}
		}
	}
}

bool UStorageComponent::ThrowOut_Server_Validate(const FPackItmeStruct& packItmeStruct)
{
	return true;
}

void UStorageComponent::UpdataData_Implementation(int Index)
{
	IObjectPacksackInterface::UpdataData_Implementation(Index);

	IObjectPacksackInterface*ObjectPacksackInterface = CastChecked<IObjectPacksackInterface>(UGameplayStatics::GetGameInstance(this)->GetFirstLocalPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()));

	if (ObjectPacksackInterface)
	{
		ObjectPacksackInterface->Execute_UpdataData(UGameplayStatics::GetGameInstance(this)->GetFirstLocalPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()),Index);
	}
	//CastChecked<UPacksackComponent>(UGameplayStatics::GetGameInstance(this)->GetFirstLocalPlayerController()->GetPawn()->GetComponentByClass(UPacksackComponent::StaticClass()));
}

void UStorageComponent::ReMoveItem_Implementation(const FPackItmeStruct& packItmeStruct)
{
	IObjectPacksackInterface::ReMoveItem_Implementation(packItmeStruct);

	ThrowOut(packItmeStruct);
}

void UStorageComponent::AddItem_Implementation(const FPackItmeStruct& packItmeStruct)
{
	IObjectPacksackInterface::AddItem_Implementation(packItmeStruct);
	//Data
}

