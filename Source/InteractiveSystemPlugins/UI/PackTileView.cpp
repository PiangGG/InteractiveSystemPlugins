// Fill out your copyright notice in the Description page of Project Settings.


#include "PackTileView.h"

void UPackTileView::SetWidgetEntry(TSubclassOf<UUserWidget> EntryWidget)
{
	EntryWidgetClass = EntryWidget;
}
