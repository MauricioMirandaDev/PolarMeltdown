
#include "PolarGameModeBase.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
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
	}
}

// Created a 2D array of tiles
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
		PlayerController->Possess(NewPlayer);
}

/*
* How to access tile : GridColumns[x].GridRows[y]
*
* EX: GridColumns[4].GridRows[2]
*/