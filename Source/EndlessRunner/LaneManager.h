// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementController.h"
#include "Obstacle.h"
#include "ObstacleSpawner.h"
#include "GameFramework/Actor.h"
#include "LaneManager.generated.h"

UCLASS()
class ENDLESSRUNNER_API ALaneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaneManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	TArray<FVector> Lanes;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMovementController> PlayerBP;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AObstacleSpawner> ObstacleSpawner;
	
};
