// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionArea.generated.h"

class UWidgetComponent;
class USphereComponent;
class UNiagaraSystem;

UCLASS()
class UEWAVESYSTEM_API AExplosionArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionArea();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	float FuseTime = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	float Damage = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Explosion|VFX")
	UNiagaraSystem* ExplodeNiagara = nullptr;
	
	UFUNCTION(BlueprintCallable, Category="Explosion")
	void Explode();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UWidgetComponent* ExplosionUI;
	
	void SpawnExplosionVFX();
private:
	FTimerHandle FuseTimer;
	
};
