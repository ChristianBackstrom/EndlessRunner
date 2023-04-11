// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"

// Sets default values
AMovementController::AMovementController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovementController::BeginPlay()
{
	Super::BeginPlay();

	Currentlane = 0;
}

// Called every frame
void AMovementController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMovementController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMovementController::Move);
	}
}

void AMovementController::Move(const FInputActionValue& Value)
{
	Currentlane += Value.Get<float>();

	Currentlane = FMath::Clamp(Currentlane,0, Lanes.Num() - 1);

	MoveToLane(Currentlane);
}

void AMovementController::MoveToLane(int32 index)
{
	SetActorLocation(Lanes[index]);
}


