// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UGameManager::PlayerHit()
{
	Lives--;

	if (Lives <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		Lives = 0;
		Score = 0;
		GameSpeed = 1;
	}
}

