
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PolarPlayerController.generated.h"

class UInputAction;
class APolarCharacter; 

UCLASS()
class POLARMELTDOWN_API APolarPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Set default values
	APolarPlayerController();

	// Called when the game starts
	virtual void BeginPlay() override; 

	void SetDebugTextColor(FColor Color);

	// Getter and setter functions to access OwningCharacter
	APolarCharacter* GetOwningCharacter(); 

	void SetOwningCharacter(APolarCharacter* PolarCharacter);

protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	// Components, functions, and variables for enhanced input system 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_SelectDirection;

	void CallMove();

	void CallSelectDirection(const FInputActionValue& Value);

	APolarCharacter* OwningCharacter; 

	FColor DebugTextColor; 
};
