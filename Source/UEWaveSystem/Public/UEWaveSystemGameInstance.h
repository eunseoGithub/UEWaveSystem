// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UEWaveSystemGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEWAVESYSTEM_API UUEWaveSystemGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Score")
	void AddScore(int32 Delta);
	
	UFUNCTION(BlueprintCallable, Category="Score")
	int32 GetScore();
	
	UFUNCTION(BlueprintCallable, Category="Score")
	void ResetScore();
public:
	UPROPERTY(BlueprintReadOnly, Category="Score")
	int32 Score = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Level = 1;
};
