
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

	FColor DebugTextColor; 

	// Getter and setter functions to access OwningCharacter
	APolarCharacter* GetOwningCharacter(); 

	void SetOwningCharacter(APolarCharacter* PolarCharacter);

	// Getter and setter functions to access bCanMove
	bool GetCanMove();

	void SetCanMove(bool bNewCanMove);

	// Getter and setter functions to access bLerpActive
	bool GetLerpActive();

	void SetLerpActive(bool bNewLerpActive);

	// Getter and setter functions to access bHasDiagonalAbility
	bool GetHasDiagonalAbility();

	void SetHasDiagonalAbility(bool bNewHasAbility);

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

	void StopShowingDirection();

	APolarCharacter* OwningCharacter; 

	// Components for gameplay
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	bool bCanMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	bool bLerpActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	bool bHasDiagonalAbility;

	class APolarGameModeBase* GameModeRef;
};
