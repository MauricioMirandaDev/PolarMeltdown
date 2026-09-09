
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FTileCoordinates
{
	GENERATED_BODY()

	int32 XCoordinate;

	int32 YCoordinate;

	FTileCoordinates() 
	{
		XCoordinate = 0;
		YCoordinate = 0;
	}

	FTileCoordinates(int32 XCoord, int32 YCoord)
	{
		XCoordinate = XCoord;
		YCoordinate = YCoord;
	}
};

UCLASS()
class POLARMELTDOWN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter and setter functions for TileCoordinates
	FTileCoordinates GetTileCoordinates(); 

	void SetTileCoordinates(int32 XCoord, int32 YCoord);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Visual components 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TileMesh;

	// Gameplay components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FTileCoordinates TileCoordinates; 
};
