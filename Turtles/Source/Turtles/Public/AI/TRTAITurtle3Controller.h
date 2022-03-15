// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TRTBaseAIController.h"
#include "TRTAITurtle3Controller.generated.h"

UCLASS()
class TURTLES_API ATRTAITurtle3Controller : public ATRTBaseAIController
{
	GENERATED_BODY()

public:
	ATRTAITurtle3Controller();

protected:
	virtual bool MoveToFinish() override;

	void MoveToReverseFinish();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reverse Point")
	FName ReversePointTag{"ReverseThirdFinish"};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float TimeInMotionToFinish{1.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float TimeInMotionToReverseFinish{0.5f};

private:
	UPROPERTY()
	AActor* ReverseTargetPoint{nullptr};

	bool IsTimerReverseMove{false};
};
