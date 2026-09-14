
#include "PolarGameModeBase.h"
#include "Engine/DataTable.h"
#include "PolarMeltdown/PUblic/Actors/Grid.h"
#include "PolarMeltdown/Public/Actors/Tile.h"

// Set default values
APolarGameModeBase::APolarGameModeBase()
{

}

// Call BeginPlay() on actors
void APolarGameModeBase::StartPlay()
{
	Super::StartPlay();

	FVector SpawnLocation = FVector(0.0f);
	FRotator SpawnRotation = FRotator(0.0f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GridClass)
	{
		FString ContextString = TEXT("Context String");
		SelectedMap = PolarGameDataTable->FindRow<FMapInfo>(TEXT("Square"), ContextString);

		if (SelectedMap)
		{
			GameGrid = GetWorld()->SpawnActor<AGrid>(GridClass, SpawnLocation, SpawnRotation, SpawnParameters);
			GameGrid->CreateGrid(SelectedMap); 
		}
	}

	/*
	TODO:
	Spawn player at beginning tile*/
}
