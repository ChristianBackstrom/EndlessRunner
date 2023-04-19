// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FJsonObject;

// USTRUCT()
// struct FHighScore
// {
// 	GENERATED_BODY();
//
// public:
// 	
// 	UPROPERTY()
// 	int HighScores;
// };


class ENDLESSRUNNER_API FileHandler
{
	
public:
	
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage);

	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);

	// static FHighScore ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	// static void WriteStructToJsonFile(FString JsonFilePath, FHighScore HighScore, bool& bOutSuccess, FString& OutInfoMessage);
};

