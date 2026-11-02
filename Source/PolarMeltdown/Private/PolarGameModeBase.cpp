
#include "PolarGameModeBase.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PolarMeltdown/Public/Actors/DirectionalArrows.h"
#include "PolarMeltdown/Public/Actors/Tile.h"
#include "PolarMeltdown/Public/Characters/PolarCharacter.h"
#include "PolarMeltdown/Public/Controllers/PolarPlayerController.h"

// Set default values
APolarGameModeBase::APolarGameModeBase()
{
	SelectedMap = nullptr; 
	PlayerOne = nullptr;
	PlayerTwo = nullptr;
}

// Call BeginPlay() on actors
void APolarGameModeBase::StartPlay()
{
	Super::StartPlay();

	FString ContextString = TEXT("Context String");
	SelectedMap = PolarGameDataTable->FindRow<FMapInfo>(TEXT("Square"), ContextString);

	if (SelectedMap)
	{
		InitializeGrid();
		CurrentPlayer = PlayerOne;

		StartPlayerTurn();
	}
}

// Prepare variables before linear interpolation
void APolarGameModeBase::PreparePlayerMove()
{
	CurrentPlayer->SetLerpActive(true);

	CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetPerpendicularArrowsVisible(false);
	CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetDiagonalArrowsVisible(false);

	TileToRemove = TileTrace(CurrentPlayer->GetOwningCharacter()->GetActorLocation(), CurrentPlayer->GetOwningCharacter()->GetActorLocation() - FVector(0.0f, 0.0f, 500.0f));

	FVector MovementDirection = CurrentPlayer->GetOwningCharacter()->EndLocation - CurrentPlayer->GetOwningCharacter()->StartLocation;
	MovementDirection.Normalize();

	CurrentPlayer->GetOwningCharacter()->SetActorRotation(MovementDirection.Rotation());
}

// Reset variables once linear interpolation is complete
void APolarGameModeBase::EndPlayerMove()
{
	CurrentPlayer->SetLerpActive(false);

	CurrentPlayer->GetOwningCharacter()->StartLocation = CurrentPlayer->GetOwningCharacter()->GetActorLocation();
	CurrentPlayer->GetOwningCharacter()->EndLocation = CurrentPlayer->GetOwningCharacter()->GetActorLocation();
	CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetActorRotation(FRotator::ZeroRotator);

	if (TileToRemove)
		GridColumns[TileToRemove->GetTileCoordinates().XCoordinate].GridRows[TileToRemove->GetTileCoordinates().YCoordinate]->DestroyTile();

	StartPlayerTurn();
}

// Use linear interpolation to move the player across tiles
void APolarGameModeBase::LerpCharacterLocation(float Alpha)
{
	FVector LerpedLocation = FMath::Lerp(CurrentPlayer->GetOwningCharacter()->StartLocation, CurrentPlayer->GetOwningCharacter()->EndLocation, Alpha);

	CurrentPlayer->GetOwningCharacter()->SetActorLocation(LerpedLocation);
}

void APolarGameModeBase::StartPlayerTurn()
{
	ATile* CurrentTile = TileTrace(CurrentPlayer->GetOwningCharacter()->GetActorLocation(), CurrentPlayer->GetOwningCharacter()->GetActorLocation() - FVector(0.0f, 0.0f, 500.0f));
	if (CurrentTile)
	{
		IterateThroughTileNeighbors(CurrentTile->GetTileCoordinates().XCoordinate, CurrentTile->GetTileCoordinates().YCoordinate);

		if (!CurrentPlayer->GetCanMove())
			EndPlayerTurn();
	}
}

void APolarGameModeBase::EndPlayerTurn()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, CurrentPlayer->DebugTextColor, TEXT("CANNOT MOVE"));
}

// Creat a 2D array of tiles
void APolarGameModeBase::InitializeGrid()
{
	if (TileClass)
	{
		FVector SpawnLocation = FVector::ZeroVector;
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int x = 0; x < SelectedMap->MapWidth; x++)
		{
			FTileRow NewRow = FTileRow(); 

			// Spawn a tile wherever there is a '9' in the map layout, skip spaces where there is a '0', spawn a player at spaces designed '1' through '4'
			for (int y = 0; y < SelectedMap->MapLength; y++)
			{
				TCHAR CurrentChar = SelectedMap->MapLayout[(x * SelectedMap->MapWidth) + y];
				ATile* NewTile;

				switch (CurrentChar)
				{
					case '1':
						NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParameters);
						NewTile->SetTileCoordinates(x, y);

						PlayerOne = Cast<APolarPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
						if (PlayerOne)
						{
							PlayerOne->SetDebugTextColor(FColor::Red);
							InitializePlayer(PlayerOne, NewTile->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), FRotator::ZeroRotator);
						}

						NewRow.GridRows.Add(NewTile);
						break;
					case '2':
						NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParameters);
						NewTile->SetTileCoordinates(x, y);

						UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
						PlayerTwo = Cast<APolarPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));
						if (PlayerTwo)
						{
							PlayerTwo->SetDebugTextColor(FColor::Blue);
							InitializePlayer(PlayerTwo, NewTile->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), FRotator::ZeroRotator);
						}

						NewRow.GridRows.Add(NewTile);
						break;
					case '9':
						NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParameters);
						NewTile->SetTileCoordinates(x, y);
						NewRow.GridRows.Add(NewTile);
						break;
					default:
						break;
				}

				// Spawn the next tile 1 meter to the right
				SpawnLocation.Y += 100.0f;
			}

			// Start the next row 1 meter in front
			GridColumns.Add(NewRow);

			SpawnLocation.X -= 100.0f;
			SpawnLocation.Y = 0.0f;
		}
	}
}

// Spawn in a new player
void APolarGameModeBase::InitializePlayer(APolarPlayerController* PlayerController, FVector SpawnLocation, FRotator SpawnRotation)
{
	APolarCharacter* NewPlayer = GetWorld()->SpawnActor<APolarCharacter>(PlayerClass, SpawnLocation, SpawnRotation);

	if (NewPlayer)
	{
		PlayerController->Possess(NewPlayer);
		PlayerController->SetOwningCharacter(NewPlayer);
		NewPlayer->SetPlayerController(PlayerController);
	}
}

// Examing neighboring tiles to see if there is a space the player can move to
void APolarGameModeBase::IterateThroughTileNeighbors(int32 Column, int32 Row)
{
	int32 MinColumn = FMath::Clamp(Column - 1, 0, SelectedMap->MapWidth);
	int32 MinRow = FMath::Clamp(Row - 1, 0, SelectedMap->MapWidth);
	int32 MaxColumn = FMath::Clamp(Column + 1, 0, SelectedMap->MapWidth);
	int32 MaxRow = FMath::Clamp(Row + 1, 0, SelectedMap->MapWidth);

	int32 NumOfOpenTiles = 0;

	for (int x = MinColumn; x <= MaxColumn; x++)
	{
		for (int y = MinRow; y <= MaxRow; y++)
		{
			// Don't examine the tile the player is currently standing on
			if (x != Column || y != Row)
			{
				switch (x - Column)
				{
				case -1:
					switch (y - Row)
					{
					case -1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy() && CurrentPlayer->GetHasDiagonalAbility())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_ForwardLeft);
							NumOfOpenTiles++;
						}
						break;
					case 1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy() && CurrentPlayer->GetHasDiagonalAbility())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_ForwardRight);
							NumOfOpenTiles++;
						}
						break;
					default:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_Forward);
							NumOfOpenTiles++;
						}
						break;
					}
					break;
				case 1:
					switch (y - Row)
					{
					case -1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy() && CurrentPlayer->GetHasDiagonalAbility())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_BackwardLeft);
							NumOfOpenTiles++;
						}
						break;
					case 1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy() && CurrentPlayer->GetHasDiagonalAbility())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_BackwardRight);
							NumOfOpenTiles++;
						}
						break;
					default:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_Backward);
							NumOfOpenTiles++;
						}
						break;
					}
					break;
				default:
					switch (y - Row)
					{
					case -1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_Left);
							NumOfOpenTiles++;
						}
						break;
					case 1:
						if (!GridColumns[x].GridRows[y]->GetIsEmtpy())
						{
							CurrentPlayer->GetOwningCharacter()->GetDirectionalArrows()->SetSingleArrowVisible(true, EArrowDirection::ARROW_Right);
							NumOfOpenTiles++;
						}
						break;
					default:
						break;
					}
					break;
				}
			}
		}
	}

	if (NumOfOpenTiles > 0)
		CurrentPlayer->SetCanMove(true);
	else
		CurrentPlayer->SetCanMove(false);
}

// Perform a line trace to get the last tile the current player was previously standing on
ATile* APolarGameModeBase::TileTrace(FVector TraceStart, FVector TraceEnd)
{
	// Variables for line trace
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(CurrentPlayer->GetOwningCharacter());

	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectTypes, true, ActorsToIgnore, EDrawDebugTrace::None, OUT HitResult, true);
	ATile* Tile = Cast<ATile>(HitResult.GetActor());

	return Tile;
}

// Check to see if there is a tile the player can move to
bool APolarGameModeBase::CanMoveToTile()
{
	ATile* DestinationTile = TileTrace(CurrentPlayer->GetOwningCharacter()->EndLocation, CurrentPlayer->GetOwningCharacter()->EndLocation - FVector(0.0f, 0.0f, 500.0f));
	if (DestinationTile)
		return !DestinationTile->GetIsEmtpy();
	else
		return false;
}

/*
* How to access tile : GridColumns[x].GridRows[y]
*
* EX: GridColumns[4].GridRows[2]
*/