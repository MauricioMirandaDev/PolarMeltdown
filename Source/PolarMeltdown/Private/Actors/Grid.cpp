
#include "Actors/Grid.h"
#include "Kismet/KismetSystemLibrary.h"
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

	// Populate the grid with a 2D array of tiles
	if (TileClass)
	{
		FVector SpawnLocation = FVector(0.0f);
		FRotator SpawnRotation = FRotator(0.0);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int x = 0; x < 5; x++) // WIDTH / COLUMNS
		{
			FTileRow NewRow = FTileRow(); 

			for (int y = 0; y < 3; y++) // HEIGHT / ROWS
			{
				ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParameters);
				NewTile->SetTileCoordinates(x, y); 
				NewRow.GridRows.Add(NewTile);

				SpawnLocation.X += 100.0f;
			}

			GridColumns.Add(NewRow);

			SpawnLocation.Y += 100.0f;
			SpawnLocation.X = 0.0f;
		}

		/*
		* How to access tile : GridColumns[x coordinate].GridRows[y]
		* 
		* EX: GridColumns[4].GridRows[2]
		*/
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

