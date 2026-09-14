
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PolarMeltdown/Public/MapInfo.h"
#include "PolarGameModeBase.generated.h"

class AGrid;
class ATile;

UCLASS()
class POLARMELTDOWN_API APolarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values
	APolarGameModeBase();

	// Calls BeginPlay() on actors
	virtual void StartPlay() override;

protected:

private:
	// Components for gameplay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGrid> GridClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDataTable* PolarGameDataTable; 

	// Grid actor spawned in game
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AGrid* GameGrid; 

	FMapInfo* SelectedMap;
};
