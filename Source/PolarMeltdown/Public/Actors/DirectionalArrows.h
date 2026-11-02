// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionalArrows.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EArrowDirection : uint8 {
	ARROW_Forward UMETA(DisplayName = "Forward Arrow"),
	ARROW_Backward UMETA(DisplayName = "Backward Arrow"),
	ARROW_Left UMETA(DisplayName = "Left Arrow"),
	ARROW_Right UMETA(DisplayName = "Right Arrow"),
	ARROW_ForwardLeft UMETA(DisplayName = "Forward-Left Arrow"),
	ARROW_ForwardRight UMETA(DisplayName = "Forward-Right Arrow"),
	ARROW_BackwardLeft UMETA(DisplayName = "Backward-Left Arrow"),
	ARROW_BackwardRight UMETA(DisplayName = "Backward-Right Arrow"),
};

UCLASS()
class POLARMELTDOWN_API ADirectionalArrows : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectionalArrows();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Functions for gameplay
	void SetSingleArrowVisible(bool bShowArrow, EArrowDirection ArrowDirection);

	void SetPerpendicularArrowsVisible(bool bShowPerpArrows);

	void SetDiagonalArrowsVisible(bool bShowDiagArrows);

	void ShowDesiredDirection(FVector Direction);

	void ResetDirection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Visual components 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ForwardArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BackwardArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ForwardLeftArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ForwardRightArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BackwardLeftArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BackwardRightArrow;

	// Components and functions for gameplay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrows", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> PerpendicularArrows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrows", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> DiagonalArrows;

	void SetDirection(UStaticMeshComponent* Arrow);
};
