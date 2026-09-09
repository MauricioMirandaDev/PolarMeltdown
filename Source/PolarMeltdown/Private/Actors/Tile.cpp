
#include "Actors/Tile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create scene component and set as root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Create static mesh component
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	TileMesh->SetupAttachment(Root);

	TileCoordinates = FTileCoordinates(0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Getter function to access TileCoordinates
FTileCoordinates ATile::GetTileCoordinates()
{
	return TileCoordinates;
}

// Setter function to assign values to TileCoordinates variables
void ATile::SetTileCoordinates(int32 XCoord, int32 YCoord)
{
	TileCoordinates.XCoordinate = XCoord;
	TileCoordinates.YCoordinate = YCoord; 
}

