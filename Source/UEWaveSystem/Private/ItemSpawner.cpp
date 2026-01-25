// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "ItemBase.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SetRootComponent(SpawnBox);
	
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnBox->SetGenerateOverlapEvents(false);
	
	SpawnBox->SetBoxExtent(FVector(300.f,300.f,50.f));
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (bAutoSpawn)
	{
		StartAutoSpawn();
	}
}

void AItemSpawner::StartAutoSpawn()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AItemSpawner::SpawnTick,
		SpawnInterval,
		true,
		InitialDelay
		);
}

void AItemSpawner::SpawnTick()
{
	SpawnBatch();
}

void AItemSpawner::CleanupAliveList()
{
	AliveItems.RemoveAll([](AActor* Actor)
	{
		return !IsValid(Actor);
	});
}

TSubclassOf<AItemBase> AItemSpawner::PickRandomItemClass() const
{
	if (ItemPool.Num()==0) return nullptr;
	const int32 Index = FMath::RandRange(0, ItemPool.Num()-1);
	return ItemPool[Index];
}

FVector AItemSpawner::GetRandomPointInBox() const
{
	const FVector Origin = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();
	
	const FVector RandPoint = Origin + FVector(
		FMath::FRandRange(-Extent.X, Extent.X),
		FMath::FRandRange(-Extent.Y, Extent.Y),
		FMath::FRandRange(-Extent.Z, Extent.Z)
		);
	
	return RandPoint + FVector(0.f,0.f,ZOffset);
}

void AItemSpawner::SpawnBatch()
{
	CleanupAliveList();
	
	if (ItemPool.Num()==0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemPool is empty"));
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	int32 SpawnCount = BatchSpawnCount;
	
	if (MaxAlive > 0)
	{
		const int32 Available = MaxAlive - AliveItems.Num();
		if (Available <=0) return;
		SpawnCount = FMath::Min(SpawnCount, Available);
	}
	
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = SpawnCollisionHandlingMethod;
	Params.Owner = this;
	
	for (int32 i = 0 ; i < SpawnCount ;++i)
	{
		const TSubclassOf<AItemBase> PickedClass = PickRandomItemClass();
		if (!PickedClass) continue;
		
		const FVector SpawnLoc = GetRandomPointInBox();
		const FRotator SpawnRot = FRotator::ZeroRotator;
		
		AItemBase* Spawned = World->SpawnActor<AItemBase>(PickedClass, SpawnLoc, SpawnRot, Params);
		if (Spawned)
		{
			AliveItems.Add(Spawned);
		}
	}
}
