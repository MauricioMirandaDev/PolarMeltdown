
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PolarMeltdown/Public/MapInfo.h"
#include "PolarGameModeBase.generated.h"

class ATile;
class APolarCharacter; 
class APolarPlayerController; 

USTRUCT(BlueprintType)
struct FTileRow
{
	GENERATED_BODY()

	TArray<ATile*> GridRows;

	FTileRow()
	{
		GridRows.Empty();
	}
};

UCLASS()
class POLARMELTDOWN_API APolarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values
	APolarGameModeBase();

	// Calls BeginPlay() on actors
	virtual void StartPlay() override;

	// Events and functions for gameplay
	UFUNCTION(BlueprintImplementableEvent)
	void MovePlayer();

	UFUNCTION(BlueprintCallable)
	void PreparePlayerMove();

	UFUNCTION(BlueprintCallable)
	void EndPlayerMove();

	UFUNCTION(BlueprintCallable)
	void LerpCharacterLocation(float Alpha);

	void StartPlayerTurn();

	void EndPlayerTurn();

	bool CanMoveToTile();

protected:

private:
	// Components, functions, and variables for gameplay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APolarCharacter> PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDataTable* PolarGameDataTable; 

	void InitializeGrid();

	void InitializePlayer(APolarPlayerController* PlayerController, FVector SpawnLocation, FRotator SpawnRotation);

	void IterateThroughTileNeighbors(int32 Column, int32 Row);

	ATile* TileTrace(FVector TraceStart, FVector TraceEnd);

	TArray<FTileRow> GridColumns;

	FMapInfo* SelectedMap;

	ATile* TileToRemove;

	// Player controller references
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Players", meta = (AllowPrivateAccess = "true"))
	APolarPlayerController* PlayerOne;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Players", meta = (AllowPrivateAccess = "true"))
	APolarPlayerController* PlayerTwo;

	APolarPlayerController* CurrentPlayer;
};
