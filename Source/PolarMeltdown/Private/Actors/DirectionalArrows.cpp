
#include "Actors/DirectionalArrows.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADirectionalArrows::ADirectionalArrows()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create scene component and set as root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Create static mesh components for each directional arrow
	ForwardArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(Root);

	BackwardArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backward Arrow"));
	BackwardArrow->SetupAttachment(Root);

	LeftArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Arrow"));
	LeftArrow->SetupAttachment(Root);

	RightArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Arrow"));
	RightArrow->SetupAttachment(Root);

	ForwardLeftArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward Left Arrow"));
	ForwardLeftArrow->SetupAttachment(Root);

	ForwardRightArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward Right Arrow"));
	ForwardRightArrow->SetupAttachment(Root);

	BackwardLeftArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backward Left Arrow"));
	BackwardLeftArrow->SetupAttachment(Root);

	BackwardRightArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Backward Right Arrow"));
	BackwardRightArrow->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADirectionalArrows::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	// Add arrows to their respective arrays
	PerpendicularArrows.Add(ForwardArrow);
	PerpendicularArrows.Add(BackwardArrow);
	PerpendicularArrows.Add(LeftArrow);
	PerpendicularArrows.Add(RightArrow);

	DiagonalArrows.Add(ForwardLeftArrow);
	DiagonalArrows.Add(ForwardRightArrow);
	DiagonalArrows.Add(BackwardLeftArrow);
	DiagonalArrows.Add(BackwardRightArrow);
}

// Called every frame
void ADirectionalArrows::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Show or hide perpendicular arrows
void ADirectionalArrows::SetPerpendicularArrowsVisible(bool bShowPerpArrows)
{
	for (UStaticMeshComponent* Arrow : PerpendicularArrows)
		Arrow->SetHiddenInGame(!bShowPerpArrows);
}

// Show or hide diagonal arrows
void ADirectionalArrows::SetDiagonalArrowsVisible(bool bShowDiagArrows)
{
	for (UStaticMeshComponent* Arrow : DiagonalArrows)
		Arrow->SetHiddenInGame(!bShowDiagArrows);
}

// Show the desired direction the player wants to move in
void ADirectionalArrows::ShowDesiredDirection(FVector ForwardVector, FVector RightVector, FVector Direction)
{
	float DotProduct = FVector::DotProduct(ForwardVector, Direction);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	if (Angle == 0.0f)
	{
		ResetDirection();
		SetDirection(ForwardArrow);
	}
	else if (Angle == 90.0f)
	{
		ResetDirection();
		
		if (FVector::DotProduct(RightVector, Direction) >= 0.0f)
			SetDirection(RightArrow);
		else
			SetDirection(LeftArrow);
	}
	else if (Angle == 180.0f)
	{
		ResetDirection();
		SetDirection(BackwardArrow);
	}
}

// Increase the scale of the arrow showing the player's desired direction
void ADirectionalArrows::SetDirection(UStaticMeshComponent* Arrow)
{
	Arrow->SetRelativeScale3D(FVector(0.25f));
}

// Reset the scale of all arrows
void ADirectionalArrows::ResetDirection()
{
	for (UStaticMeshComponent* Arrow : PerpendicularArrows)
		Arrow->SetRelativeScale3D(FVector(0.1f));

	for (UStaticMeshComponent* Arrow : DiagonalArrows)
		Arrow->SetRelativeScale3D(FVector(0.1f));
}
