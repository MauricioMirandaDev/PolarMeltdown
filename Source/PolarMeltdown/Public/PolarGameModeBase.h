
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PolarGameModeBase.generated.h"

class AGrid;
class ATile;

UCLASS()
class POLARMELTDOWN_API APolarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values
	APolarGameModeBase();

	// Calls BeginPlay() on actors
	virtual void StartPlay() override;

protected:

private:
	// Components for gameplay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGrid> GridClass;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AGrid* GameGrid; 
};
