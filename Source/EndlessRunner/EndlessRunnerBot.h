// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaneManager.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerBot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObstacleInFront);

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerBot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndlessRunnerBot();

protected:
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FOnObstacleInFront OnObstacleInFront;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float BaseChanceToAvoid;

	float  ChanceToAvoid;

	UPROPERTY(EditAnywhere)
	float AvoidanceDistance;
	
	UPROPERTY(EditAnywhere)
	float FreeLaneCheckLength;
	
	UPROPERTY(EditAnywhere)
	FVector Offset;
	
	UPROPERTY(EditInstanceOnly)
	ALaneManager* LaneManager;

	TArray<FVector> Lanes;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<FVector> FreeLanes;

	UPROPERTY(EditAnywhere)
	float AvoidCooldown;
	
	float Timer = 0;

private:

	UFUNCTION()
	void ObstacleInFront();

	void MoveToLane(int32 Index);
};
