// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TRTAICharacter.h"
#include "AI/TRTBaseAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ATRTAICharacter::ATRTAICharacter() : Super()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ATRTBaseAIController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void ATRTAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(SpawnSound);
	check(DeathSound);

	check(SpawnNiagaraSystem);
	check(DeathNiagaraSystem);

	check(GetMesh());

	PlaySpawnEffects();
}

void ATRTAICharacter::Die()
{
	PlayDeathEffects();

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ATRTAICharacter::PlaySpawnEffects() const
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
		SpawnNiagaraSystem,									   //
		GetActorLocation(),									   //
		GetActorLocation().Rotation());
}

void ATRTAICharacter::PlayDeathEffects() const
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
		DeathNiagaraSystem,									   //
		GetActorLocation(),									   //
		GetActorLocation().Rotation());
}