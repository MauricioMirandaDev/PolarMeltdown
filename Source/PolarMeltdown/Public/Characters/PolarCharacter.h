
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PolarCharacter.generated.h"

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
	UFUNCTION(BlueprintCallable)
	void LerpPlayerLocation(float Alpha); 

	UFUNCTION(BlueprintCallable)
	void FinishMove();

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanMove; 

	FVector StartLocation;

	FVector EndLocation;
};
