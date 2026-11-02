
#include "Controllers/PolarPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "PolarMeltdown/Public/PolarGameModeBase.h"
#include "PolarMeltdown/Public/Actors/DirectionalArrows.h"
#include "PolarMeltdown/Public/Characters/PolarCharacter.h"

// Sets default values
APolarPlayerController::APolarPlayerController()
{
	InputMappingContext = nullptr;

	InputAction_Move = nullptr;
	InputAction_SelectDirection = nullptr;

	OwningCharacter = nullptr;
	DebugTextColor = FColor::Red;
	bCanMove = true;
	bLerpActive = false;
	bHasDiagonalAbility = true;
	GameModeRef = nullptr;
}

// Called when the game starts
void APolarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the game mode
	GameModeRef = Cast<APolarGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef == nullptr)
		return;
}

void APolarPlayerController::SetDebugTextColor(FColor Color)
{
	DebugTextColor = Color; 
}

// Getter function to access OwningCharacter
APolarCharacter* APolarPlayerController::GetOwningCharacter()
{
	return OwningCharacter;
}

// Setter function to set OwningCharacter
void APolarPlayerController::SetOwningCharacter(APolarCharacter* PolarCharacter)
{
	OwningCharacter = PolarCharacter;
}

// Getter function to access bCanMove
bool APolarPlayerController::GetCanMove()
{
	return bCanMove;
}

// Setter function to set bCanMove
void APolarPlayerController::SetCanMove(bool bNewCanMove)
{
	bCanMove = bNewCanMove;
}

// Getter function to access bLerpActive
bool APolarPlayerController::GetLerpActive()
{
	return bLerpActive;
}

// Setter function to set bLerpActive
void APolarPlayerController::SetLerpActive(bool bNewLerpActive)
{
	bLerpActive = bNewLerpActive;
}

// Getter function to access bNewHasAbility
bool APolarPlayerController::GetHasDiagonalAbility()
{
	return bHasDiagonalAbility;
}

// Setter function to set bNewHasAbility
void APolarPlayerController::SetHasDiagonalAbility(bool bNewHasAbility)
{
	bHasDiagonalAbility = bNewHasAbility;
}

// Called to bind functionality to input
void APolarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add mapping context to controller
	UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (LocalSubsystem)
	{
		LocalSubsystem->ClearAllMappings();
		LocalSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	// Bind actions to input system
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(InputAction_Move, ETriggerEvent::Triggered, this, &APolarPlayerController::CallMove);
		EnhancedInput->BindAction(InputAction_SelectDirection, ETriggerEvent::Triggered, this, &APolarPlayerController::CallSelectDirection);
		EnhancedInput->BindAction(InputAction_SelectDirection, ETriggerEvent::Completed, this, &APolarPlayerController::StopShowingDirection);
	}
}

// Move the character once the player has selected a direction
void APolarPlayerController::CallMove()
{
	if (!bLerpActive && bCanMove && OwningCharacter->EndLocation.Size() != 0.0f && GameModeRef->CanMoveToTile())
	{
		FVector Direction = OwningCharacter->EndLocation - OwningCharacter->StartLocation;
		Direction.Normalize();

		GameModeRef->MovePlayer();
	}
}

// Select the direction for the player to move in
void APolarPlayerController::CallSelectDirection(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (!bLerpActive && bCanMove)
	{
		float XDirection = FMath::RoundToFloat(MovementValue.Y);
		float YDirection = FMath::RoundToFloat(MovementValue.X);

		FVector Direction = FVector(XDirection, YDirection, 0.0f);
		Direction.Normalize();

		OwningCharacter->StartLocation = OwningCharacter->GetActorLocation();
		OwningCharacter->EndLocation = OwningCharacter->StartLocation;

		// Set end location based on direction
		if (Direction.X < 0.0f)
			OwningCharacter->EndLocation.X -= 100.0f;
		else if (Direction.X > 0.0f)
			OwningCharacter->EndLocation.X += 100.0f;

		if (Direction.Y < 0.0f)
			OwningCharacter->EndLocation.Y -= 100.0f;
		else if (Direction.Y > 0.0f)
			OwningCharacter->EndLocation.Y += 100.0f;

		OwningCharacter->Arrows->ShowDesiredDirection(Direction);
	}
}

// Stop selecting a direction
void APolarPlayerController::StopShowingDirection()
{
	OwningCharacter->Arrows->ResetDirection();
}


