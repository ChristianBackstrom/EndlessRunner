// Fill out your copyright notice in the Description page of Project Settings.


#include "LaneManager.h"
#include "MovementController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaneManager::ALaneManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaneManager::BeginPlay()
{
	Super::BeginPlay();


	AMovementController* player = GetWorld()->SpawnActor<AMovementController>(PlayerBP, Lanes[1], FRotator::ZeroRotator);

	player->Lanes = Lanes;
	player->MoveToLane(0);
}

// Called every frame
void ALaneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

