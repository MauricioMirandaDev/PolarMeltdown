
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

	// Getter and setter functions for bIsEmpty
	bool GetIsEmtpy();

	void SetIsEmtpy(bool bEmpty);

	// Functions for gameplay
	void DestroyTile();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	FTileCoordinates TileCoordinates; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	bool bIsEmpty; 
};
