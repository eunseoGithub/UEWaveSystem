// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSystemGameModeBase.h"

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
	
	WaveManagerRef->OnAllWaveFinished.AddDynamic(this, &AWaveSystemGameModeBase::HandleAlllWaveFinished);
	
	
}

void AWaveSystemGameModeBase::HandleAlllWaveFinished()
{
	if (NextLevelName.IsNone()) return;
	
	UGameplayStatics::OpenLevel(this, NextLevelName);
}
