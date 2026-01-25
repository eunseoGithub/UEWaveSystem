// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionItem.h"

#include "TagManager.h"
#include "UEWaveSystem/UEWaveSystemCharacter.h"

// Sets default values
APotionItem::APotionItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemTag = TAG_ITEM_POTION;
}

// Called when the game starts or when spawned
void APotionItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 20.f * DeltaTime; 
	SetActorRotation(NewRotation);
}

void APotionItem::ItemActive(AActor* Activator)
{
	if (!Activator) return;
	
	AUEWaveSystemCharacter* Player = Cast<AUEWaveSystemCharacter>(Activator);
	if (!Player) return;
	
	Player->AddHp(HpAmount);
	DestroyItem();
}

