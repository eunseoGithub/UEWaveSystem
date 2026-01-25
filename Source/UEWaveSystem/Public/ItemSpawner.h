// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class AItemBase;
class UBoxComponent;

UCLASS()
class UEWAVESYSTEM_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();
	
	UFUNCTION(BlueprintCallable, Category="Item Spawner")
	void SpawnBatch();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Item Spawner")
	UBoxComponent* SpawnBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Item Spawner")
	TArray<TSubclassOf<AItemBase>> ItemPool;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Spawner", meta=(ClampMin="1"))
	int32 BatchSpawnCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Spanwer")
	bool bAutoSpawn = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Spanwer", meta=(ClampMin="0.01"))
	float SpawnInterval = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Spawner",meta=(ClampMin="0.0"))
	float InitialDelay = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Spawner",meta=(ClampMin="0"))
	int32 MaxAlive = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Spanwer")
	float ZOffset = 0.0f;
private:
	FTimerHandle SpawnTimer;
	
	UPROPERTY()
	TArray<AActor*> AliveItems;
	
	void CleanupAliveList();
	void StartAutoSpawn();
	void SpawnTick();
	
	TSubclassOf<AItemBase> PickRandomItemClass() const;
	FVector GetRandomPointInBox() const;
};
