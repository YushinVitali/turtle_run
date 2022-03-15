// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TRTCoreTypes.h"
#include "TRTGameModeBase.generated.h"

class ATRTPlayerStart;
class AAIController;

UCLASS()
class TURTLES_API ATRTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATRTGameModeBase();

	virtual void StartPlay() override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void SpawnBot(ETRTTypeOfRespawn Type);

private:
	void FillSpawns();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "")
	TArray<FInfoTurtleNest> InfoTurtleNests;

private:
	UPROPERTY()
	TMap<ETRTTypeOfRespawn, ATRTPlayerStart*> Spawns;
};
