
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PolarGameModeBase.generated.h"

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

};
