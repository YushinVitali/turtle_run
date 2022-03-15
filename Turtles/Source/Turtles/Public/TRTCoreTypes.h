#pragma once

#include "TRTCoreTypes.generated.h"


UENUM(BlueprintType)
enum class ETRTTypeOfRespawn : uint8
{
	Player = 0,
	Nest1,
	Nest2,
	Nest3,
	Empty
};

class ATRTBaseAIController;
class APawn;

USTRUCT(BlueprintType)
struct FInfoTurtleNest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info Turtle Nest")
	TSubclassOf<ATRTBaseAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info Turtle Nest")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info Turtle Nest")
	ETRTTypeOfRespawn TypeOfRespawn;
};