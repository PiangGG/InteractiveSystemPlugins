// Fill out your copyright notice in the Description page of Project Settings.


#include "Packsack_List_Item_Object.h"

#include "Net/UnrealNetwork.h"

UPacksack_List_Item_Object::UPacksack_List_Item_Object()
{
	PackItme  = FPackItmeStruct();
}

UPacksack_List_Item_Object::UPacksack_List_Item_Object(FPackItmeStruct& PackItmeStruct)
{
	PackItme = PackItmeStruct;
}

void UPacksack_List_Item_Object::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPacksack_List_Item_Object,PackItme);
}

void UPacksack_List_Item_Object::SetPackItme(FPackItmeStruct& PackItmeStruct)
{
	PackItme = PackItmeStruct;
}

void UPacksack_List_Item_Object::SetPackItmeData(FPackItmeStruct PackItmeStruct)
{
	PackItme = PackItmeStruct;
}

FPackItmeStruct UPacksack_List_Item_Object::GetObjectData_Implementation(UObject* Object)
{
	
	return PackItme;
}

UUserWidget* UPacksack_List_Item_Object::GetParent()
{
	return  Parent;
}

void UPacksack_List_Item_Object::SetParent(UUserWidget* parent)
{
	Parent = parent;
}
