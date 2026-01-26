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
#include "UEWaveSystemGameInstance.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

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
	
	PlayerHP = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPUI"));
	PlayerHP->SetupAttachment(GetRootComponent());
	PlayerHP->SetWidgetSpace(EWidgetSpace::Screen);
	PlayerHP->SetRelativeLocation(FVector(0.f,0.f,120.f));
	PlayerHP->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
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
	UpdateOverheadHP();
}

void AUEWaveSystemCharacter::Damage(int32 Amount)
{
	Hp = FMath::Clamp(Hp- Amount,MinHp,Hp);
	UE_LOG(LogTemp,Log,TEXT("HP : %d"),Hp);
	UpdateOverheadHP();
}

void AUEWaveSystemCharacter::UpdateOverheadHP() const
{
	if (!PlayerHP) return;
	UUserWidget* RawWidget = PlayerHP->GetUserWidgetObject();
	if (!RawWidget) return;
	UTextBlock* HPText = Cast<UTextBlock>(RawWidget->GetWidgetFromName(TEXT("PlayerHp")));
	UProgressBar* HPImage = Cast<UProgressBar>(RawWidget->GetWidgetFromName(TEXT("HP_ProgressBar")));
	if (!HPText||!HPImage) return;
	HPText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Hp, MaxHp)));
	const float Ratio = Hp/FMath::Max(MaxHp,1.f);
	HPImage->SetPercent(Ratio);
	UUEWaveSystemGameInstance* GI = GetGameInstance<UUEWaveSystemGameInstance>();
	if (!GI) return;
	GI->CurrentPlayerHP = Hp;
}

void AUEWaveSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (StatusWidgetClass)
	{
		PlayerHP->SetWidgetClass(StatusWidgetClass);
	}
	UUEWaveSystemGameInstance* GI = GetGameInstance<UUEWaveSystemGameInstance>();
	if (!GI) return;
	Hp = GI->CurrentPlayerHP;
	UpdateOverheadHP();
}
