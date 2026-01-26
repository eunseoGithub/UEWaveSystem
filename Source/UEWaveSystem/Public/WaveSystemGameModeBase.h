// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveSystemGameModeBase.generated.h"

class AWaveManager;

UCLASS()
class UEWAVESYSTEM_API AWaveSystemGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	AWaveManager* WaveManagerRef = nullptr;
	
	UFUNCTION()
	void HandleAllWaveFinished();
private:
	UPROPERTY(EditAnywhere, Category="Wave|Travel")
	TArray<FName> NextLevelName;
	int32 CurrentIndex = 0;
};