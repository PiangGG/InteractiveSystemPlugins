// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSubsystem.h"

#include "Engine/DataTable.h"
#include "InteractiveSystemPlugins/Data/PackItemData.h"

UInteractiveSubsystem::UInteractiveSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemList(TEXT("DataTable'/InteractiveSystemPlugins/PacItemkList/DT_PackItemList.DT_PackItemList'"));
	DT = ItemList.Object;
	
}

FPackItmeDataStruct* UInteractiveSubsystem::GetStructData(const FPackItmeStruct& packItmeStruct)
{
	return DT->FindRow<FPackItmeDataStruct>(packItmeStruct.Name,TEXT(""));
}
