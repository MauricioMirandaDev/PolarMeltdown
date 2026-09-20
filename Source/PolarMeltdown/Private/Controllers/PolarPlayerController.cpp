
#include "Controllers/PolarPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APolarPlayerController::APolarPlayerController()
{
	InputMappingContext = nullptr;
	InputAction_Select = nullptr;
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
		EnhancedInput->BindAction(InputAction_Select, ETriggerEvent::Triggered, this, &APolarPlayerController::CallSelect);
	}
}

void APolarPlayerController::CallSelect()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, DebugTextColor, TEXT("SELECT PRESSED"));
	}
}


