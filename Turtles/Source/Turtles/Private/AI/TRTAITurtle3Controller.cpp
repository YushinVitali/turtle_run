// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TRTAITurtle3Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "TRTCoreTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogTRTAITurtle3Controller, All, All);

ATRTAITurtle3Controller::ATRTAITurtle3Controller()
{
	TypeOfRespawn = ETRTTypeOfRespawn::Nest3;
	TargetPointTag = "ThirdFinish";
}

bool ATRTAITurtle3Controller::MoveToFinish()
{
	const bool IsFinish{Super::MoveToFinish()};
	if (!IsFinish && !IsTimerReverseMove)
	{
		FTimerHandle TimeToStopMove;
		GetWorldTimerManager().SetTimer(
			TimeToStopMove, this, &ATRTAITurtle3Controller::MoveToReverseFinish, TimeInMotionToFinish, false);
		IsTimerReverseMove = true;
	}

	return IsFinish;
}

void ATRTAITurtle3Controller::MoveToReverseFinish()
{
	IsCanMoveForward = false;

	if (!GetPawn())
	{
		UE_LOG(LogTRTAITurtle3Controller, Error, TEXT("No controllable Pawn!"));
		return;
	}

	if (!ReverseTargetPoint)
	{
		TArray<AActor*> TargetPoints;
		UGameplayStatics::GetAllActorsOfClassWithTag(
			GetWorld(), ATargetPoint::StaticClass(), ReversePointTag, TargetPoints);
		if (TargetPoints.Num() == 0)
		{
			UE_LOG(LogTRTAITurtle3Controller, Error, TEXT("ReverseTargetPoint not found!"));
			ReverseTargetPoint = nullptr;
			return;
		}
		else
		{
			ReverseTargetPoint = TargetPoints[0];
		}
	}

	MoveToActor(ReverseTargetPoint);

	FTimerHandle TimeToMove;
	FTimerDelegate SwitchMoveFlag;
	SwitchMoveFlag.BindLambda([&]() {
		IsCanMoveForward = true;
		IsTimerReverseMove = false;
	});
	GetWorldTimerManager().SetTimer(TimeToMove, SwitchMoveFlag, TimeInMotionToReverseFinish, false);
}