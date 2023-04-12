// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
	
	if (Timer >= Cooldown)
	{
		Timer = 0;
		Cooldown = FMath::RandRange(.4f, 1.f);

		int randomObstacle = FMath::RandRange(0, ObstaclesToSpawn.Num() - 1);

		int randomLane = FMath::RandRange(0, Lanes.Num() - 1);

		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstaclesToSpawn[randomObstacle], Lanes[randomLane] + FVector(1000, 0,0), FRotator::ZeroRotator);

		Obstacle->GameSpeed = GameSpeed;

		SpawnedObstacles.Add(Obstacle);
	}
}

