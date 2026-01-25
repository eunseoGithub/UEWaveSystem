// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "UEWaveSystem/UEWaveSystemCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName((TEXT("OverlapAllDynamic")));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemOverlap);
	
	
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}


void AItemBase::OnItemOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;
	UE_LOG(LogTemp, Log, TEXT("Item Overlap : %s"),
	*OtherActor->GetName());
	UE_LOG(LogTemp, Log, TEXT("Item Tag : %s"),*GetItemTag().ToString());
	for (const FName& Tag : OtherActor->Tags)
	{
		UE_LOG(LogTemp, Log, TEXT(" - Actor Tag : %s"),
			*Tag.ToString());
	}
	AUEWaveSystemCharacter* Character = Cast<AUEWaveSystemCharacter>(OtherActor);
	const FGameplayTag PlayerTag = FGameplayTag::RequestGameplayTag(FName("Player"));
	
	if (Character && Character->GetTag() == PlayerTag)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green,FString::Printf(TEXT("Overlap!")));
		ItemActive(OtherActor);
	}
}

void AItemBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	
}

void AItemBase::ItemActive(AActor* Activator)
{
}

FGameplayTag AItemBase::GetItemTag() const
{
	return ItemTag;
}

void AItemBase::DestroyItem()
{
	Destroy();
}

