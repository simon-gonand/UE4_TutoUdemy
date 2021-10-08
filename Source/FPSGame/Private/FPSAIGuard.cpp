// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnPawnHeared);	
	OriginalRotation = this->GetActorRotation();
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr || AFPSGameMode::bIsGameOver)
		return;
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
	ACharacter* character = Cast<ACharacter>(SeenPawn);
	if (character) {
		AFPSGameMode* gameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode) {
			gameMode->CompleteMission(character, false);
			PawnSensingComp->bSeePawns = false;
		}
	}
}

void AFPSAIGuard::OnPawnHeared(APawn* HearedPawn, const FVector& NoiseLocation, float HearedVolume)
{
	if (HearedPawn == nullptr)
		return;

	UE_LOG(LogTemp, Log, TEXT("Actor Heared"));
	
	
	FVector Direction = NoiseLocation - this->GetActorLocation();
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetRotation, 3.0f, false);
}

void AFPSAIGuard::ResetRotation()
{
	SetActorRotation(OriginalRotation);
}

