// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class AItemBase;
class UBoxComponent;

USTRUCT(BlueprintType)
struct FSpawnerWaveParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BatchCount = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialDelay = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAlive = 0;
};

UCLASS()
class UEWAVESYSTEM_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();
	UFUNCTION()
	void SetSpawnWaveParams(FSpawnerWaveParams Params);
protected:
	virtual void BeginPlay() override;
	
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* SpawnBox = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Pool")
	TArray<TSubclassOf<AItemBase>> ItemPool;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Rule")
	float ZOffset = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Legacy")
	bool bAutoSpawn = false;
	
private:
	FTimerHandle SpawnTimer;
	
	UPROPERTY()
	TArray<AItemBase*> AliveItems;
	FSpawnerWaveParams CurrentParam;
public:
	void CleanupAliveList();
	void SpawnBatch();
	
	TSubclassOf<AItemBase> PickRandomItemClass() const;
	FVector GetRandomPointInBox() const;
};
