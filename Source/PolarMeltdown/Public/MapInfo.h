
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapInfo.generated.h"

USTRUCT(BlueprintType)
struct FMapInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MapWidth;

	UPROPERTY(EditAnywhere)
	int32 MapLength;

	UPROPERTY(EditAnywhere)
	FString MapLayout;

	FMapInfo()
	{
		MapWidth = 0;
		MapLength = 0;
		MapLayout = TEXT("");
	}
};