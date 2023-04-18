// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	int Lives = 3;

	UFUNCTION(BlueprintCallable)
	void PlayerHit();

	UPROPERTY(BlueprintReadOnly)
	float GameSpeed = 1;
};