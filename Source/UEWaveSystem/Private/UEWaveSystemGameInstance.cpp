// Fill out your copyright notice in the Description page of Project Settings.


#include "UEWaveSystemGameInstance.h"

void UUEWaveSystemGameInstance::AddScore(int32 Delta)
{
	if (Delta == 0) return;
	Score += Delta;
}

int32 UUEWaveSystemGameInstance::GetScore()
{
	return Score;
}

void UUEWaveSystemGameInstance::ResetScore()
{
	Score = 0;
}
