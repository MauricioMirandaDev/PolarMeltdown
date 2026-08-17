
#include "PolarGameModeBase.h"

// Set default values
APolarGameModeBase::APolarGameModeBase()
{

}

// Call BeginPlay() on actors
void APolarGameModeBase::StartPlay()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("STARTING GAME"));
}
