// Fill out your copyright notice in the Description page of Project Settings.


#include "BombItem.h"

#include "TagManager.h"

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
	
}

