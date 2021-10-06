// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractedZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractedZone : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AFPSExtractedZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
