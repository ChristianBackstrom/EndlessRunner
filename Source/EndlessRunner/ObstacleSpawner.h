// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GameSpeed = 1;

	TArray<FVector> Lanes;

private:
	float Timer;

	float Cooldown;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AObstacle>> ObstaclesToSpawn;

	TArray<AObstacle*> SpawnedObstacles;
};
