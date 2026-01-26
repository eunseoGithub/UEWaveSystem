// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "UEWaveSystemCharacter.generated.h"

class UWidgetComponent;

UCLASS(Blueprintable)
class AUEWaveSystemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEWaveSystemCharacter();
	
	FGameplayTag GetTag() const;
	
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	int32 GetHp() const;
	void AddHp(int32 Amount);
	void Damage(int32 Amount);
	
	void UpdateOverheadHP() const;
protected:
	virtual void BeginPlay() override;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	int32 Hp = 100;
	int32 MaxHp = 100;
	int32 MinHp = 0;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="UI")
	UWidgetComponent* PlayerHP;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	TSubclassOf<UUserWidget> StatusWidgetClass;
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Tags")
	FGameplayTag Tag;
};

