// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TRTAICharacter.generated.h"

class USoundCue;
class UNiagaraSystem;

UCLASS()
class TURTLES_API ATRTAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATRTAICharacter();

	void Die();

protected:
	virtual void BeginPlay() override;

private:
	void PlaySpawnEffects() const;
	void PlayDeathEffects() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* DeathSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* SpawnNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* DeathNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Death")
	float LifeSpanOnDeath{3.0f};
};
