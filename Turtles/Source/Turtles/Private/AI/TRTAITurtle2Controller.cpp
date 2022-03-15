// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TRTAITurtle2Controller.h"
#include "TRTCoreTypes.h"

ATRTAITurtle2Controller::ATRTAITurtle2Controller()
{
	TypeOfRespawn = ETRTTypeOfRespawn::Nest2;
	TargetPointTag = "SecondFinish";
}

bool ATRTAITurtle2Controller::MoveToFinish()
{
	const bool IsFinish{Super::MoveToFinish()};
	if (!IsFinish && !IsTimerStop)
	{
		FTimerHandle TimeToStopMove;
		GetWorldTimerManager().SetTimer(TimeToStopMove, this, &ATRTAITurtle2Controller::Stop, TimeInMotion, false);
		IsTimerStop = true;
	}

	return IsFinish;
}

void ATRTAITurtle2Controller::Stop()
{
	IsCanMoveForward = false;
	StopMovement();

	FTimerHandle TimeToMove;
	FTimerDelegate SwitchMoveFlag;
	SwitchMoveFlag.BindLambda([&]() {
		IsCanMoveForward = true;
		IsTimerStop = false;
	});
	GetWorldTimerManager().SetTimer(TimeToMove, SwitchMoveFlag, StopTime, false);
}