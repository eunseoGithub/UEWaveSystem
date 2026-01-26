// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSystemGameModeBase.h"

#include "UEWaveSystemGameInstance.h"
#include "WaveManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AWaveSystemGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority()) return;
	
	WaveManagerRef = Cast<AWaveManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(),AWaveManager::StaticClass()));
	
	if (!IsValid(WaveManagerRef)) return;
	
	WaveManagerRef->OnAllWaveFinished.AddDynamic(this, &AWaveSystemGameModeBase::HandleAllWaveFinished);
	UUEWaveSystemGameInstance * GI = GetGameInstance<UUEWaveSystemGameInstance>();
	if (!GI) return;
	CurrentIndex = GI->CurrentLevelIndex;
	
}

void AWaveSystemGameModeBase::HandleAllWaveFinished()
{
	if (NextLevelName.IsEmpty()) return;

	UUEWaveSystemGameInstance* GI = GetGameInstance<UUEWaveSystemGameInstance>();
	if (!GI) return;

	if (CurrentIndex >= NextLevelName.Num())
	{
		GI->Level = 1;
		CurrentIndex = 0;

		UGameplayStatics::OpenLevel(this, FName("L_GameStartlevel"));
	}
	else
	{
		UGameplayStatics::OpenLevel(this, NextLevelName[CurrentIndex]);
		
		GI->Level++;
		GI->CurrentLevelIndex++;	
	}
}
