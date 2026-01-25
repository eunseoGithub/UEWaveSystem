// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "UEWaveSystemCharacter.generated.h"

UCLASS(Blueprintable)
class AUEWaveSystemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEWaveSystemCharacter();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Tags")
	FGameplayTag Tag;
	FGameplayTag GetTag() const;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	int32 GetHp() const;
	void AddHp(int32 Amount);
	void Damage(int32 Amount);
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	int32 Hp = 50;
	int32 MaxHp = 100;
	int32 MinHp = 0;
	
	
};

