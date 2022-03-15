// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TRTBaseAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "TRTCoreTypes.h"
#include "AI/TRTAICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogTRTBaseAIController, All, All);

ATRTBaseAIController::ATRTBaseAIController()
{
	bWantsPlayerState = true;
}

void ATRTBaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPawn() && GetTargetPoint())
	{
		if (MoveToFinish())
		{
			UE_LOG(LogTRTBaseAIController, Error, TEXT("Destroy Actor..."));
			Cast<ATRTAICharacter>(GetPawn())->Die();
			Destroy();
		}
	}
}

ETRTTypeOfRespawn ATRTBaseAIController::GetTypeRespawn() const
{
	return TypeOfRespawn;
}

void ATRTBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

bool ATRTBaseAIController::MoveToFinish()
{
	if (!IsCanMoveForward)
	{
		return false;
	}

	if (!GetPawn())
	{
		UE_LOG(LogTRTBaseAIController, Error, TEXT("No controllable Pawn!"));
		return false;
	}

	const auto Point{GetTargetPoint()};
	if (Point)
	{
		return MoveToActor(Point, -1.0f, false) == EPathFollowingRequestResult::AlreadyAtGoal;
	}
	return false;
}

AActor* ATRTBaseAIController::GetTargetPoint() {
	if (!TargetPoint)
	{
		TArray<AActor*> TargetPoints;
		UGameplayStatics::GetAllActorsOfClassWithTag(
			GetWorld(), ATargetPoint::StaticClass(), TargetPointTag, TargetPoints);
		if (TargetPoints.Num() == 0)
		{
			UE_LOG(LogTRTBaseAIController, Error, TEXT("TargetPoint not found!"));
			TargetPoint = nullptr;
		}
		else
		{
			TargetPoint = TargetPoints[0];
		}
	}

	return TargetPoint;
}