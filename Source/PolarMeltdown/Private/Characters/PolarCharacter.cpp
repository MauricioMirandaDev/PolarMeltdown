
#include "Characters/PolarCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PolarMeltdown/Public/PolarGameModeBase.h"
#include "PolarMeltdown/Public/Actors/DirectionalArrows.h"
#include "PolarMeltdown/Public/Actors/Tile.h"
#include "PolarMeltdown/Public/Controllers/PolarPlayerController.h"

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

	bIsPlayerTurn = true;
	Arrows = nullptr; 
	GameModeRef = nullptr; 
	StartLocation = FVector(0.0f);
	EndLocation = FVector(0.0f);
}

// Getter function to access Arrows
ADirectionalArrows* APolarCharacter::GetDirectionalArrows()
{
	return Arrows;
}

// Setter function to set ControllerRef
void APolarCharacter::SetPlayerController(APolarPlayerController* NewController)
{
	ControllerRef = NewController;
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
		Arrows->SetPerpendicularArrowsVisible(false);
		Arrows->SetDiagonalArrowsVisible(false);
	}

	// Get a reference to the game mode
	GameModeRef = Cast<APolarGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef == nullptr)
		return;
}

// Called every frame
void APolarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


