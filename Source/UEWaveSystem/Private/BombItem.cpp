// Fill out your copyright notice in the Description page of Project Settings.


#include "BombItem.h"

#include "ExplosionArea.h"
#include "TagManager.h"
#include "UEWaveSystem/UEWaveSystemCharacter.h"

// Sets default values
ABombItem::ABombItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemTag = TAG_ITEM_BOMB;
}

// Called when the game starts or when spawned
void ABombItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABombItem::ItemActive(AActor* Activator)
{
	if (!Activator) return;
	AUEWaveSystemCharacter* Player = Cast<AUEWaveSystemCharacter>(Activator);
	if (!Player) return;
	
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AExplosionArea * Area = GetWorld()->SpawnActor<AExplosionArea>(
		ExplosionAreaActor,
		GetActorLocation(),
		FRotator::ZeroRotator,
		Params
		);
	if (!Area) return;
	DestroyItem();
}

