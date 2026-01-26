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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void SetSpawnerData(UWaveDataAsset* CurrentWave) const;
	void WaveOn();
	void InitialTime();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	float CurrentDuration = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	bool bTimerOn = false;
private:
	int32 CurrentWaveIndex = 0;
	float CurrentWaveDelay = 0.0f;
};
