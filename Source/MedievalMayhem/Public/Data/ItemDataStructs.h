#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	float number;
};