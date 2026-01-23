// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

#include "TagManager.h"

// Sets default values
ACoinItem::ACoinItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemTag = TAG_ITEM_COIN;
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinItem::ItemActive(AActor* Activator)
{
	
}

