// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerBot.h"

// Sets default values
AEndlessRunnerBot::AEndlessRunnerBot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEndlessRunnerBot::BeginPlay()
{
	Super::BeginPlay();

	Lanes = LaneManager->Lanes;
	FreeLanes = Lanes;
	ChanceToAvoid = BaseChanceToAvoid;

	MoveToLane(0);
	
	OnObstacleInFront.AddDynamic(this, &AEndlessRunnerBot::ObstacleInFront);
}


// Called every frame
void AEndlessRunnerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	for (int i = 0; i < Lanes.Num(); ++i)
	{
		FVector Start = Lanes[i] + Offset;
		FVector End = FVector::ForwardVector * FreeLaneCheckLength + Start;
		FCollisionQueryParams CollisionParams;
		FHitResult OutHit;
		
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
		{
			FreeLanes.Remove(Lanes[i]);
		}
		else
		{
			FreeLanes.AddUnique(Lanes[i]);
		}
	}

	FVector Start = GetActorLocation();
	FVector End = FVector::ForwardVector * AvoidanceDistance + Start;
	FCollisionQueryParams CollisionParams;
	FHitResult OutHit;

	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams) && Timer >= AvoidCooldown)
	{
		Timer = 0;
		if (!FreeLanes.IsEmpty())
			OnObstacleInFront.Broadcast();
	}
}


void AEndlessRunnerBot::ObstacleInFront()
{
	bool bShouldAvoid = FMath::RandRange(0.f, 1.f) < ChanceToAvoid;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, bShouldAvoid ? FColor::Green : FColor::Red, bShouldAvoid ? "Avoided" : "Did not avoid");

	if (bShouldAvoid)
	{
		ChanceToAvoid -= BaseChanceToAvoid / 100;
		int Index = FMath::RandRange(0, FreeLanes.Num() - 1);

		for (int i = 0; i < Lanes.Num(); ++i)
		{
			if (Lanes[i] == FreeLanes[Index])
			{
				Index = i;
				break;
			}
		}
		
		MoveToLane(Index);
		return;
	}

	ChanceToAvoid = BaseChanceToAvoid;
}

void AEndlessRunnerBot::MoveToLane(int32 Index)
{
	Index = FMath::Clamp(Index, 0, Lanes.Num()-1);
	SetActorLocation(Lanes[Index] + Offset);
}



