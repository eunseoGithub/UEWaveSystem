// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "BombItem.generated.h"

UCLASS()
class UEWAVESYSTEM_API ABombItem :  public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ItemActive(AActor* Activator) override;


};
