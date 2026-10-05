
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	// Components for enhanced input system 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_Select;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_MoveUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_MoveDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_MoveLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_MoveRight;

	void CallSelect();

	void CallMoveUp();

	void CallMoveDown();

	void CallMoveLeft();

	void CallMoveRight(); 

	APolarCharacter* OwningCharacter; 

	FColor DebugTextColor; 
};
