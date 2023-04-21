// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "FileHandler.h"
#include "Kismet/GameplayStatics.h"

void UGameManager::PlayerHit()
{
	Lives--;

	if (Lives <= 0)
	{
		int score = FMath::RoundToInt(Score * 100);
		bool bOutSuccess;
		FString OutMessageInfo;
		FString scoreString = FileHandler::ReadStringFromFile("C:/Temp/HighScore.txt", bOutSuccess, OutMessageInfo);
		if (!bOutSuccess)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, OutMessageInfo);
			FileHandler::WriteStringToFile("C:/Temp/HighScore.txt", FString::FromInt(score), bOutSuccess, OutMessageInfo);

			if (!bOutSuccess)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, OutMessageInfo);
			}
		}
		else
		{
			scoreString.Append(" ");
			scoreString.Append(FString::FromInt(score));

			FileHandler::WriteStringToFile("C:/Temp/HighScore.txt", scoreString, bOutSuccess, OutMessageInfo);

			if (!bOutSuccess)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, OutMessageInfo);
			}
		}
		
		
		Lives = 3;
		Score = 0;
		GameSpeed = 1;
		
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	}
}

FString UGameManager::GetHighScore()
{
	bool bOutSuccess;
	FString OutMessageInfo;
	return FileHandler::ReadStringFromFile("C:/Temp/HighScore.txt", bOutSuccess, OutMessageInfo);
}


// void UGameManager::OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
// {
// 	if (GEngine)
// 		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, *Response->GetContentAsString());
// }
//
// void UGameManager::OnGetResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
// {
// 	TSharedPtr<FJsonObject> ResponseObj;
// 	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
// 	FJsonSerializer::Deserialize(Reader, ResponseObj);
//
// 	TArray<int32> scores;
//
//
// 	TArray<TSharedPtr<FJsonValue>> Values = ResponseObj->GetObjectField("dreamlo")->GetObjectField("leaderboard")->GetArrayField("entry");
//
// 	if (GEngine)
// 		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::SanitizeFloat(Values.Num()));
// 	
// 	for (int i = 0; i < Values.Num(); ++i)
// 	{
// 		int32 val = Values[i]->AsObject()->GetNumberField("score");
//
// 		scores.Add(val);
// 	}
//
// 	if (GEngine)
// 		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::SanitizeFloat(scores.Num()));
// 	
// 	scores.Sort([](const int& a, const int& b) { return b < a; });
//
// 	Scores = scores;
// }



