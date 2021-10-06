// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	//PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnPawnHeared);
	
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (SeenPawn == nullptr)
		return;
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
	/*ACharacter* character = Cast<ACharacter>(SeenPawn);
	if (character) {
		
	}*/
}

//void AFPSAIGuard::OnPawnHeared(APawn* HearedPawn, const FVector& PawnLocation, float HearedVolume)
//{
//	ACharacter* character = Cast<ACharacter>(HearedPawn);
//	if (character) {
//		DrawDebugSphere(GetWorld(), HearedPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
//	}
//}

