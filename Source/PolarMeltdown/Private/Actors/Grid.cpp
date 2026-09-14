
#include "Actors/Grid.h"
#include "PolarMeltdown/Public/Actors/Tile.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickEnabled(false); 
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Create a 2D array of tiles
void AGrid::CreateGrid(FMapInfo* Map)
{
	if (TileClass)
	{
		FVector SpawnLocation = FVector(0.0f);
		FRotator SpawnRotation = FRotator(0.0);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int x = 0; x < Map->MapWidth; x++) // WIDTH / COLUMNS
		{
			FTileRow NewRow = FTileRow();

			for (int y = 0; y < Map->MapLength; y++) // HEIGHT / ROWS
			{
				TCHAR CurrentChar = Map->MapLayout[(x * Map->MapWidth) + y];
				ATile* NewTile;

				// Spawn a tile wherever there is a '1' in the map layout
				switch (CurrentChar)
				{
					case '1':
						NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParameters);
						NewTile->SetTileCoordinates(x, y);
						NewRow.GridRows.Add(NewTile);
						break;
					default:
						break;
				}

				// Spawn the next tile 1 meter to the right
				SpawnLocation.X += 100.0f;
			}

			// Start the next row 1 meter in front
			GridColumns.Add(NewRow);

			SpawnLocation.Y += 100.0f;
			SpawnLocation.X = 0.0f;
		}
	}
}

/*
* How to access tile : GridColumns[x coordinate].GridRows[y]
*
* EX: GridColumns[4].GridRows[2]
*/