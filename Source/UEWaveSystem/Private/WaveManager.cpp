// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "ItemSpawner.h"
#include "WaveDataAsset.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	WaveOn();
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bTimerOn)
	{
		CurrentDuration += DeltaTime;
		RemainingTime -= DeltaTime;
		if (CurrentDuration >= Wave[CurrentWaveIndex]->Duration)
		{
			bTimerOn = false;
			Spawner->CleanupAliveList();
		}
	}
	else
	{
		CurrentWaveDelay +=DeltaTime;
		if (CurrentWaveDelay >= Wave[CurrentWaveIndex]->SpawnParms.InitialDelay)
		{
			if (Wave.Num()> CurrentWaveIndex + 1)
			{
				CurrentWaveIndex++;
				WaveOn();
			}
			else
			{
				OnAllWaveFinished.Broadcast();
			}

		}
	}
}

void AWaveManager::SetSpawnerData(UWaveDataAsset* CurrentWave) const
{
	Spawner->SetSpawnWaveParams(CurrentWave->SpawnParms);
}

void AWaveManager::WaveOn()
{
	InitialTime();
	SetSpawnerData(Wave[CurrentWaveIndex]);
	Spawner->SpawnBatch();
	bTimerOn = true;
}

void AWaveManager::InitialTime()
{
	CurrentDuration = 0.f;
	CurrentWaveDelay = 0.f;
	RemainingTime = Wave[CurrentWaveIndex]->Duration;
}

