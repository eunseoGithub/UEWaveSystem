// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemSpawner.h"
#include "WaveDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UEWAVESYSTEM_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float Duration = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FSpawnerWaveParams SpawnParms;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave|Name")
	FString WaveName;
};
