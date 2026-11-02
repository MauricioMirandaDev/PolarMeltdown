
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

// Show or hide one single arrow
void ADirectionalArrows::SetSingleArrowVisible(bool bShowArrow, EArrowDirection ArrowDirection)
{
	switch (ArrowDirection)
	{
	case EArrowDirection::ARROW_Backward:
		BackwardArrow->SetHiddenInGame(!bShowArrow);
		break;
	case EArrowDirection::ARROW_Left:
		LeftArrow->SetHiddenInGame(!bShowArrow);
		break;
	case EArrowDirection::ARROW_Right:
		RightArrow->SetHiddenInGame(!bShowArrow);
		break;
	case EArrowDirection::ARROW_ForwardLeft:
		ForwardLeftArrow->SetHiddenInGame(!bShowArrow);
		break;
	case EArrowDirection::ARROW_ForwardRight:
		ForwardRightArrow->SetHiddenInGame(!bShowArrow);
		break;
	case EArrowDirection::ARROW_BackwardLeft:
		BackwardLeftArrow->SetHiddenInGame(!bShowArrow);
	case EArrowDirection::ARROW_BackwardRight:
		BackwardRightArrow->SetHiddenInGame(!bShowArrow);
		break;
	default:
		ForwardArrow->SetHiddenInGame(!bShowArrow);
		break;
	}
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
void ADirectionalArrows::ShowDesiredDirection(FVector Direction)
{
	float DotProduct = FVector::DotProduct(GetActorForwardVector(), Direction);
	int32 Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	switch (Angle)
	{
	case 45:
		ResetDirection();

		if (FVector::DotProduct(GetActorRightVector(), Direction) >= 0.0f)
			SetDirection(ForwardRightArrow);
		else
			SetDirection(ForwardLeftArrow);
		break;
	case 90:
		ResetDirection();

		if (FVector::DotProduct(GetActorRightVector(), Direction) >= 0.0f)
			SetDirection(RightArrow);
		else
			SetDirection(LeftArrow);
		break;
	case 135:
		ResetDirection();

		if (FVector::DotProduct(GetActorRightVector(), Direction) >= 0.0f)
			SetDirection(BackwardRightArrow);
		else
			SetDirection(BackwardLeftArrow);
		break;
	case 180:
		ResetDirection();
		SetDirection(BackwardArrow);
		break;
	default:
		ResetDirection();
		SetDirection(ForwardArrow);
		break;
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
