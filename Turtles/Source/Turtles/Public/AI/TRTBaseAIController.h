// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TRTCoreTypes.h"
#include "TRTBaseAIController.generated.h"

UCLASS()
class TURTLES_API ATRTBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATRTBaseAIController();

	virtual void Tick(float DeltaTime) override;

	ETRTTypeOfRespawn GetTypeRespawn() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual bool MoveToFinish();

	AActor* GetTargetPoint();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Type Respawn")
	ETRTTypeOfRespawn TypeOfRespawn{ETRTTypeOfRespawn::Nest1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Finish Point")
	FName TargetPointTag{"FirstFinish"};

	UPROPERTY()
	AActor* TargetPoint{nullptr};

	bool IsCanMoveForward{true};
};
