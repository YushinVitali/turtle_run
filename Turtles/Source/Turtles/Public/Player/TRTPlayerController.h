// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TRTCoreTypes.h"
#include "TRTPlayerController.generated.h"


UCLASS()
class TURTLES_API ATRTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ETRTTypeOfRespawn GetTypeRespawn() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Type")
	ETRTTypeOfRespawn TypeOfRespawn{ETRTTypeOfRespawn::Player};
};
