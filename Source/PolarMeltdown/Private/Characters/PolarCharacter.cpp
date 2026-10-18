
#include "Characters/PolarCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PolarMeltdown/Public/Actors/DirectionalArrows.h"

// Sets default values
APolarCharacter::APolarCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm component and set default values
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// Create camera component and set default values
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bCanMove = true;
	Arrows = nullptr; 
	StartLocation = FVector(0.0f);
	EndLocation = FVector(0.0f);
}

// Getter function to access Arrows
ADirectionalArrows* APolarCharacter::GetArrows()
{
	return Arrows;
}

// Called when the game starts or when spawned
void APolarCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false); 

	// Spawn directional arrows and set this character as the parent
	if (ArrowClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Arrows = GetWorld()->SpawnActor<ADirectionalArrows>(ArrowClass, GetActorLocation(), GetActorRotation(), SpawnParameters);
		Arrows->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Arrows->SetOwner(this);
		Arrows->SetPerpendicularArrowsVisible(true);
		Arrows->SetDiagonalArrowsVisible(false);
	}
}

// Called every frame
void APolarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Use a linear interploation to move the player's location
void APolarCharacter::LerpPlayerLocation(float Alpha)
{
	FVector LerpedLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);

	SetActorLocation(LerpedLocation);
}

// Set variables before linear interpolation
void APolarCharacter::PrepareMove()
{
	bCanMove = false;
	Arrows->SetPerpendicularArrowsVisible(false);

	FVector MovementDirection = EndLocation - StartLocation;
	MovementDirection.Normalize();

	SetActorRotation(MovementDirection.Rotation());
}

// Reset StartLocation and EndLocation
void APolarCharacter::FinishMove()
{
	bCanMove = true;
	Arrows->SetPerpendicularArrowsVisible(true);

	StartLocation = GetActorLocation();
	EndLocation = GetActorLocation(); 
}


