// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/TRTGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ATRTGameHUD::BeginPlay()
{
	check(HUDWidgetClass);

	HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
}

void ATRTGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ATRTGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize{5.0f};
	const float LineThickness{1.0f};
	const FLinearColor LineColor{FLinearColor::Green};

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}