// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TRTCoreTypes.h"
#include "TRTButton.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInstanceConstant;
class UTextRenderComponent;
class ATRTAIController;
class AAIController;
class USoundCue;

UCLASS()
class TURTLES_API ATRTButton : public AActor
{
	GENERATED_BODY()

public:
	ATRTButton();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Activate();

private:
	void UnActivate();
	void SpawnTurtle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* ButtonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* PlatformMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Material")
	UMaterialInstanceConstant* SelectedButtonMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Material")
	UMaterialInstanceConstant* DefaultButtonMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Label")
	UTextRenderComponent* TextComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* ButtonPressedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	ETRTTypeOfRespawn TypeOfRespawn{ETRTTypeOfRespawn::Nest1};

private:
	bool IsActive{false};
};
