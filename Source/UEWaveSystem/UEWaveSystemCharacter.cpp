// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEWaveSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "TagManager.h"
AUEWaveSystemCharacter::AUEWaveSystemCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	Tag = TAG_PLAYER;
}

FGameplayTag AUEWaveSystemCharacter::GetTag() const
{
	return Tag;
}

void AUEWaveSystemCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

int32 AUEWaveSystemCharacter::GetHp() const
{
	return Hp;
}

void AUEWaveSystemCharacter::AddHp(int32 Amount)
{
	Hp = FMath::Clamp(Hp + Amount,0.f,MaxHp);
	UE_LOG(LogTemp,Log,TEXT("HP : %d"),Hp);
}

void AUEWaveSystemCharacter::Damage(int32 Amount)
{
	Hp = FMath::Clamp(Hp- Amount,MinHp,Hp);
	UE_LOG(LogTemp,Log,TEXT("HP : %d"),Hp);
}
