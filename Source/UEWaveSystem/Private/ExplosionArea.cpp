// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionArea.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UEWaveSystem/UEWaveSystemCharacter.h"
// Sets default values
AExplosionArea::AExplosionArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName((TEXT("OverlapAllDynamic")));
	
	ExplosionUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExplosionWidget"));
	ExplosionUI->SetupAttachment(Collision);
	ExplosionUI->SetWidgetSpace(EWidgetSpace::World);
	ExplosionUI->SetRelativeRotation(FRotator(0.f,0.f,0.f));
	ExplosionUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ExplosionUI->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExplosionUI->SetGenerateOverlapEvents(false);
	ExplosionUI->SetRelativeLocation(FVector(0.f,0.f,2.f));
}

// Called when the game starts or when spawned
void AExplosionArea::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FuseTimer, this, &AExplosionArea::Explode,FuseTime, false);
}

void AExplosionArea::SpawnExplosionVFX() 
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	
	if (!ExplodeNiagara) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ExplodeNiagara,
		Location,
		Rotation
		);
}

void AExplosionArea::Explode()
{
	SpawnExplosionVFX();
	AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(this,0);
	if (!PlayerActor) return;
	if (Collision->IsOverlappingActor(PlayerActor))
	{
		AUEWaveSystemCharacter* PC = Cast<AUEWaveSystemCharacter>(PlayerActor);
		if (PC)
			PC->Damage(Damage);
	}
	Destroy();
}


