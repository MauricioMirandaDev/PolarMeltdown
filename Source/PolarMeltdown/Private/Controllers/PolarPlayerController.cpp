
#include "Controllers/PolarPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PolarMeltdown/Public/Characters/PolarCharacter.h"

// Sets default values
APolarPlayerController::APolarPlayerController()
{
	InputMappingContext = nullptr;

	InputAction_Move = nullptr;
	InputAction_SelectDirection = nullptr;

	OwningCharacter = nullptr;
	DebugTextColor = FColor::Red; 
}

// Called when the game starts
void APolarPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
	}
}

// Move the character once the player has selected a direction
void APolarPlayerController::CallMove()
{
	if (OwningCharacter->bCanMove && OwningCharacter->EndLocation.Size() != 0.0f)
	{
		OwningCharacter->MoveCharacter();

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, DebugTextColor, TEXT("MOVING CHARACTER"));
	}
}

// Select the direction for the player to move in
void APolarPlayerController::CallSelectDirection(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (OwningCharacter->bCanMove)
	{
		float XDirection = FMath::RoundToFloat(MovementValue.Y);
		float YDirection = FMath::RoundToFloat(MovementValue.X);

		FVector Direction = FVector(XDirection, YDirection, 0.0f);
		Direction *= 100.0f;

		OwningCharacter->StartLocation = OwningCharacter->GetActorLocation();
		OwningCharacter->EndLocation = OwningCharacter->StartLocation + Direction;
	}
}


