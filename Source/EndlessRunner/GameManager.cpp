// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

void UGameManager::PlayerHit()
{
	Lives--;

	if (Lives <= 0)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, TEXT("YOU LOST"));
	}
}

