// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "ObstacleSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacle::AObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	GameManager = Cast<UGameManager>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;

	if (LifeTime <= 0)
	{
		Destroy();
	}

	for (int i = 0; i < Players.Num(); ++i)
	{
		FVector relativeLocation = this->GetActorLocation() - Players[i]->GetActorLocation();

		if (relativeLocation.X < 0)
		{
			if (relativeLocation.Size() < HitDetectionRadius)
			{
				GameManager->PlayerHit();
				Destroy();
			}

			if (!hasBeenPassed)
			{
				float randomNumber = FMath::RandRange(0.f, 1.f);

				OnPassed.Broadcast(randomNumber < 0.2f);
				hasBeenPassed = true;
			}
		}
	}

	AddActorLocalOffset(FVector::BackwardVector * GameManager->GameSpeed * 5);
}

void AObstacle::PreviousHasBeenPassed(bool IsDestroyed)
{
	if (IsDestroyed)
	{
		Destroy();
	}
}
