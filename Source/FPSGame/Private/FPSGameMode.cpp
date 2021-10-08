// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

bool AFPSGameMode::bIsGameOver = false;

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bSuccess)
{
	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);
	}

	if (bSuccess)
		UGameplayStatics::PlaySound2D(this, SuccessSound);
	else
		UGameplayStatics::PlaySound2D(this, FailedSound);

	bIsGameOver = true;

	OnMissionComplete(InstigatorPawn, bSuccess);
}
