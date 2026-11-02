
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PolarCharacter.generated.h"

class ADirectionalArrows; 
class APolarPlayerController;
class ATile;

UCLASS()
class POLARMELTDOWN_API APolarCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APolarCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Friend class to help with input bindings
	friend class APolarPlayerController;

	// Functions for gameplay
	UFUNCTION(BlueprintImplementableEvent)
	void MoveCharacter(); 

	// Getter function for Arrows
	ADirectionalArrows* GetDirectionalArrows(); 

	// Setter function for ControllerRef
	void SetPlayerController(APolarPlayerController* NewController);

	FVector StartLocation;

	FVector EndLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components for camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// Components, functions, and variables for gameplay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADirectionalArrows> ArrowClass;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsPlayerTurn;

	ADirectionalArrows* Arrows; 

	class APolarGameModeBase* GameModeRef; 

	APolarPlayerController* ControllerRef;
};
