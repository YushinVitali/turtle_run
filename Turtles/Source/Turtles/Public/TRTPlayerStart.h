// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TRTCoreTypes.h"
#include "TRTPlayerStart.generated.h"

UCLASS()
class TURTLES_API ATRTPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ETRTTypeOfRespawn GetTypeRespawn() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	ETRTTypeOfRespawn TypeOfRespawn{ETRTTypeOfRespawn::Player};
};
