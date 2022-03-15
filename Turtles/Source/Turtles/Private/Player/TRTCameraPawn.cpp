// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TRTCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Buttons/TRTButton.h"
#include "DrawDebugHelpers.h"


DEFINE_LOG_CATEGORY_STATIC(LogTRTCameraPawn, All, All);


ATRTCameraPawn::ATRTCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 10.0f, 10.0f);
	SpringArmComponent->TargetArmLength = 20.0f;
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

void ATRTCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATRTCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATRTCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ATRTCameraPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATRTCameraPawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATRTCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATRTCameraPawn::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATRTCameraPawn::Fire);
}

void ATRTCameraPawn::MoveForward(float Amount)
{
	if (FMath::IsNearlyZero(Amount))
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), Amount);
}

void ATRTCameraPawn::MoveRight(float Amount)
{
	if (FMath::IsNearlyZero(Amount))
	{
		return;
	}

	AddMovementInput(GetActorRightVector(), Amount);
}

void ATRTCameraPawn::Fire()
{
	if (!GetWorld())
	{
		return;
	}

	const float TraceMaxDistance{2000};
	const FVector ShootDirection{GetActorForwardVector()};
	const FVector TraceStart{GetActorLocation()};
	const FVector TraceEnd{TraceStart + ShootDirection * TraceMaxDistance};

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		const auto DamageActor{Cast<ATRTButton>(HitResult.GetActor())};
		if (!DamageActor)
		{
			return;
		}

		DamageActor->Activate();
	}
}
