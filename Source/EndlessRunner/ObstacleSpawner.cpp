// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Kismet/GameplayStatics.h"

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
	Cooldown = FMath::RandRange(.4f, 1.f);

	Lanes = LaneManager->Lanes;

	GameManager = Cast<UGameManager>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;


	GameSpeed += DeltaTime * DifficultyIncreaseRate;

	GameManager->Score += DeltaTime * GameSpeed;
	GameManager->GameSpeed = GameSpeed;

	if (Timer >= Cooldown)
	{
		Timer = 0;
		Cooldown = FMath::RandRange(.4f, 1.f);
		int amount = FMath::RandRange(1, Lanes.Num() - 1);
		int LastLane = -1;

		TArray<AObstacle*> newObstacle;

		for (int i = 0; i < amount; ++i)
		{
			int randomObstacle = FMath::RandRange(0, ObstaclesToSpawn.Num() - 1);

			int randomLane = FMath::RandRange(0, Lanes.Num() - 1);


			while (randomLane == LastLane)
			{
				randomLane = FMath::RandRange(0, Lanes.Num() - 1);
			}

			FVector location = Lanes[randomLane] + FVector(2000, 0, 0);
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstaclesToSpawn[randomObstacle], location,
			                                                        FRotator::ZeroRotator);

			newObstacle.Add(Obstacle);
			Obstacle->Players = Players;
			LastLane = randomLane;

			for (int j = 0; j < LastSpawned.Num(); ++j)
			{
				LastSpawned[j]->OnPassed.AddDynamic(Obstacle, &AObstacle::PreviousHasBeenPassed);
			}
		}

		LastSpawned = newObstacle;
	}
}
