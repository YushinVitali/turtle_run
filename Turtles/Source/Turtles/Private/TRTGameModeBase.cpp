// Fill out your copyright notice in the Description page of Project Settings.

#include "TRTGameModeBase.h"
#include "Player/TRTPlayerController.h"
#include "Player/TRTPlayerState.h"
#include "UI/TRTGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "TRTPlayerStart.h"
#include "TRTCoreTypes.h"
#include "AI/TRTBaseAIController.h"
#include "Player/TRTPlayerController.h"
#include "Player/TRTCameraPawn.h"

ATRTGameModeBase::ATRTGameModeBase()
{
	DefaultPawnClass = ATRTCameraPawn::StaticClass();
	PlayerControllerClass = ATRTPlayerController::StaticClass();
	PlayerStateClass = ATRTPlayerState::StaticClass();
	HUDClass = ATRTGameHUD::StaticClass();
}

void ATRTGameModeBase::StartPlay()
{
	Super::StartPlay();

	checkf(InfoTurtleNests.Num() != 0, TEXT("Information about turtle nests is not given!"));
}

AActor* ATRTGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (Spawns.Num() == 0)
	{
		FillSpawns();
	}

	ETRTTypeOfRespawn Type = ETRTTypeOfRespawn::Empty;

	if (Player->IsA<ATRTPlayerController>())
	{
		Type = Cast<ATRTPlayerController>(Player)->GetTypeRespawn();
	}
	else if (Player->IsA<ATRTBaseAIController>())
	{
		Type = Cast<ATRTBaseAIController>(Player)->GetTypeRespawn();
	}

	return Type != ETRTTypeOfRespawn::Empty ? Spawns[Type] : nullptr;
}

void ATRTGameModeBase::SpawnBot(ETRTTypeOfRespawn Type)
{
	if (!GetWorld())
	{
		return;
	}

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const auto& InfoTurtleNest : InfoTurtleNests)
	{
		if (InfoTurtleNest.TypeOfRespawn == Type)
		{
			const auto TRTAIController{
				GetWorld()->SpawnActor<AAIController>(InfoTurtleNest.AIControllerClass, SpawnInfo)};
			RestartPlayer(TRTAIController);
		}
	}
}

void ATRTGameModeBase::FillSpawns()
{
	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATRTPlayerStart::StaticClass(), FoundPlayerStarts);

	for (const auto FoundPlayerStart : FoundPlayerStarts)
	{
		ATRTPlayerStart* PlayerStart{Cast<ATRTPlayerStart>(FoundPlayerStart)};
		if (PlayerStart)
		{
			Spawns.Add(PlayerStart->GetTypeRespawn(), PlayerStart);
		}
	}
}

UClass* ATRTGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ATRTBaseAIController* TRTBaseAIController{Cast<ATRTBaseAIController>(InController)};
	if (TRTBaseAIController)
	{
		for (const auto& InfoTurtleNest : InfoTurtleNests)
		{
			if (InfoTurtleNest.TypeOfRespawn == TRTBaseAIController->GetTypeRespawn())
			{
				return InfoTurtleNest.AIPawnClass;
			}
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
