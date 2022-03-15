// Fill out your copyright notice in the Description page of Project Settings.

#include "Buttons/TRTButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/TextRenderComponent.h"
#include "AI/TRTBaseAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TRTGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogTRTButton, All, All);

ATRTButton::ATRTButton()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(SceneComponent);

	ButtonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ButtonMeshComponent");
	ButtonMeshComponent->SetupAttachment(CollisionComponent);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("Label");
	TextComponent->SetupAttachment(SceneComponent);

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMeshComponent");
	PlatformMeshComponent->SetupAttachment(CollisionComponent);
}

void ATRTButton::BeginPlay()
{
	Super::BeginPlay();

	check(ButtonMeshComponent);
	check(PlatformMeshComponent);
	check(ButtonMeshComponent->GetStaticMesh());

	check(DefaultButtonMaterial);
	check(SelectedButtonMaterial);

	check(ButtonPressedSound);

	ButtonMeshComponent->SetMaterial(0, DefaultButtonMaterial);
}

void ATRTButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATRTButton::Activate()
{
	if (!GetWorld() || IsActive)
	{
		return;
	}

	IsActive = true;
	ButtonMeshComponent->SetMaterial(0, SelectedButtonMaterial);

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATRTButton::UnActivate, 3.0f, false);

	SpawnTurtle();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ButtonPressedSound, GetActorLocation());
}

void ATRTButton::UnActivate()
{
	if (!IsActive)
	{
		return;
	}

	ButtonMeshComponent->SetMaterial(0, DefaultButtonMaterial);
	IsActive = false;
}

void ATRTButton::SpawnTurtle()
{
	if (!GetWorld())
	{
		return;
	}

	auto GameMode{Cast<ATRTGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))};
	if (GameMode)
	{
		GameMode->SpawnBot(TypeOfRespawn);
	}
}