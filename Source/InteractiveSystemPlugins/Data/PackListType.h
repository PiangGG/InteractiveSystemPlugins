#pragma once

UENUM(BlueprintType)
enum class EPackListType :uint8
{
	List		UMETA(DisplayName = "列表"),
	Tile		UMETA(DisplayName = "瓦片")
};
