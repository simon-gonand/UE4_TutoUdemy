// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractedZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"

// Sets default values
AFPSExtractedZone::AFPSExtractedZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSExtractedZone::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComp->SetHiddenInGame(false);
}

// Called every frame
void AFPSExtractedZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSExtractedZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter* player = Cast<AFPSCharacter>(OtherActor);
	if (player) {
		if (player->bIsCarryingObjective) {
			AFPSGameMode* gameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (gameMode)
				gameMode->CompleteMission(player);
		}
		else
			UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}

