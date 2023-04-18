// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UGameManager::PlayerHit()
{
	Lives--;

	if (Lives <= 0)
	{

		FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
		Request->OnProcessRequestComplete().BindUObject(this, &UGameManager::OnResponseRecieved);
		int score = FMath::RoundToInt(Score * 100);
		int randomPlayer = FMath::RandRange(0, 100000);
		FString URL = "http://dreamlo.com/lb/yF4Mn0NSpkyrN8s5KtEIIQFLnQXBbvn0uMsc2AuoBYZw/add/";
		URL.Append(FString::FromInt(randomPlayer));
		URL.Append("/");
		URL.Append(FString::FromInt(score));
		Request->SetURL(URL);
		Request->SetVerb("GET");
		Request->ProcessRequest();
		
		
		Lives = 3;
		Score = 0;
		GameSpeed = 1;
		
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	}
}

void UGameManager::GetHighScore()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGameManager::OnGetResponseRecieved);
	int score = FMath::RoundToInt(Score * 100);
	Request->SetURL("http://dreamlo.com/lb/643e70d68f40bb6dec65520c/json");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}


void UGameManager::OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, *Response->GetContentAsString());
}

void UGameManager::OnGetResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	TArray<int32> scores;


	TArray<TSharedPtr<FJsonValue>> Values = ResponseObj->GetObjectField("dreamlo")->GetObjectField("leaderboard")->GetArrayField("entry");

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::SanitizeFloat(Values.Num()));
	
	for (int i = 0; i < Values.Num(); ++i)
	{
		int32 val = Values[i]->AsObject()->GetNumberField("score");

		scores.Add(val);
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::SanitizeFloat(scores.Num()));
	
	scores.Sort([](const int& a, const int& b) { return b < a; });

	Scores = scores;
}



