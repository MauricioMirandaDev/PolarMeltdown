
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class ATile; 

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
class AGrid : public AActor
{
	GENERATED_BODY()

	friend class APolarGameModeBase; 
	
public:	
	// Sets default values for this actor's properties
	AGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATile> TileClass;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FTileRow> GridColumns;
};
