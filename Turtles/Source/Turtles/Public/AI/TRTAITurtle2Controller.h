// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TRTBaseAIController.h"
#include "TRTAITurtle2Controller.generated.h"

UCLASS()
class TURTLES_API ATRTAITurtle2Controller : public ATRTBaseAIController
{
	GENERATED_BODY()

public:
	ATRTAITurtle2Controller();

protected:
	virtual bool MoveToFinish() override;

	void Stop();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float TimeInMotion{1.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float StopTime{0.5f};

private:
	bool IsTimerStop{false};
};
