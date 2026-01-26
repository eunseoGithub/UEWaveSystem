// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	
	if (!StartMenuWidgetClass) return;
	StartMenuWidget = CreateWidget<UUserWidget>(this,StartMenuWidgetClass);
	if (!StartMenuWidget) return;
	StartMenuWidget->AddToViewport();
	
	UButton* PlayButton = Cast<UButton>(StartMenuWidget->GetWidgetFromName(TEXT("PlayButton")));
	UButton* ExitButton = Cast<UButton>(StartMenuWidget->GetWidgetFromName(TEXT("ExitButton")));
	
	if (!PlayButton) return;
	if (!ExitButton) return;
	
	PlayButton->OnClicked.AddDynamic(this,&AStartPlayerController::OnStartClicked);
	ExitButton->OnClicked.AddDynamic(this,&AStartPlayerController::ONExitClicked);

	PrimaryActorTick.bCanEverTick = true;
}


void AStartPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AStartPlayerController::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this,FName("L_WaveOne"));
}

void AStartPlayerController::ONExitClicked()
{
	UKismetSystemLibrary::QuitGame(this,this, EQuitPreference::Quit,true);
}
