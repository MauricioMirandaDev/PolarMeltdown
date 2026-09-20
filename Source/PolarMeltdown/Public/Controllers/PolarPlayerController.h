
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PolarPlayerController.generated.h"

class UInputAction;

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

protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	// Components for enhanced input system 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input System", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction_Select;

	void CallSelect();

	FColor DebugTextColor; 
};
