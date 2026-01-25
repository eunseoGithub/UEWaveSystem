// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class UWaveDataAsset;
class AItemSpawner;
UCLASS()
class UEWAVESYSTEM_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnData")
	TArray<UWaveDataAsset*> Wave;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnData")
	AItemSpawner* Spawner;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
