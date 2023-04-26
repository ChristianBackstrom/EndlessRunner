// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "MovementController.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassed, bool, IsDestroyed);

UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PreviousHasBeenPassed(bool IsDestroyed);

public:
	TArray<AMovementController*> Players;

	FOnPassed OnPassed;
	
private:
	bool hasBeenPassed = false;
	
	UGameManager* GameManager;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	float LifeTime = 10.f;
};
