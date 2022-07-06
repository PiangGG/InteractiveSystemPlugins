// Fill out your copyright notice in the Description page of Project Settings.


#include "PackListView.h"

void UPackListView::SetWidgetEntry(TSubclassOf<UUserWidget> EntryWidget)
{
	EntryWidgetClass = EntryWidget;
}
