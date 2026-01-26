// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEWAVESYSTEM_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	
	UPROPERTY()
	UUserWidget* StartMenuWidget = nullptr;
	
	UFUNCTION()
	void OnStartClicked();
	
	UFUNCTION()
	void ONExitClicked();
};
