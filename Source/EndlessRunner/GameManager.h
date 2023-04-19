// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"
#include "Json.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int Lives = 3;
	
	UPROPERTY(BlueprintReadOnly)
	float Score = 0;


	UPROPERTY(BlueprintReadOnly)
	float GameSpeed = 1;

public:
	UFUNCTION(BlueprintCallable)
	void PlayerHit();

	UFUNCTION(BlueprintCallable)
	FString GetHighScore();
	
	// UPROPERTY(BlueprintReadOnly)
	// TArray<int32> Scores;

private:
	
	// void OnGetResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);
	// void OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);


};