// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "PotionItem.generated.h"

UCLASS()
class UEWAVESYSTEM_API APotionItem : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotionItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ItemActive(AActor* Activator) override;
private:
	int32 HpAmount = 30;
};
