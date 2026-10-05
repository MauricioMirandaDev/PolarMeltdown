
#include "Controllers/PolarPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PolarMeltdown/Public/Characters/PolarCharacter.h"

// Sets default values
APolarPlayerController::APolarPlayerController()
{
	InputMappingContext = nullptr;
	InputAction_Select = nullptr;
	InputAction_MoveUp = nullptr;
	InputAction_MoveDown = nullptr;
	InputAction_MoveLeft = nullptr;
	InputAction_MoveRight = nullptr;
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
		EnhancedInput->BindAction(InputAction_Select, ETriggerEvent::Triggered, this, &APolarPlayerController::CallSelect);
		EnhancedInput->BindAction(InputAction_MoveUp, ETriggerEvent::Triggered, this, &APolarPlayerController::CallMoveUp);
		EnhancedInput->BindAction(InputAction_MoveDown, ETriggerEvent::Triggered, this, &APolarPlayerController::CallMoveDown);
		EnhancedInput->BindAction(InputAction_MoveLeft, ETriggerEvent::Triggered, this, &APolarPlayerController::CallMoveLeft);
		EnhancedInput->BindAction(InputAction_MoveRight, ETriggerEvent::Triggered, this, &APolarPlayerController::CallMoveRight);
	}
}

void APolarPlayerController::CallSelect()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, DebugTextColor, TEXT("SELECT PRESSED"));
	}
}

void APolarPlayerController::CallMoveUp()
{
	OwningCharacter->MoveCharacter();
}

void APolarPlayerController::CallMoveDown()
{
	OwningCharacter->MoveCharacter();
}

void APolarPlayerController::CallMoveLeft()
{
	OwningCharacter->MoveCharacter();
}

void APolarPlayerController::CallMoveRight()
{
	OwningCharacter->StartLocation = OwningCharacter->GetActorLocation();
	OwningCharacter->EndLocation = OwningCharacter->GetActorLocation() + FVector(0.0f, 100.0f, 0.0f);

	OwningCharacter->MoveCharacter();
}


