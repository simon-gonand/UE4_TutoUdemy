// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* SuccessSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* FailedSound;

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionComplete(APawn* InstigatorPawn, bool bSuccess);

	static bool bIsGameOver;
};



