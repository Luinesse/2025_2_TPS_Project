// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"
#include "CrosshairInterface.h"

void UCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APawn* OwnerPawn = GetOwningPlayerPawn();

	ICrosshairInterface* Spreader = Cast<ICrosshairInterface>(OwnerPawn);
	if (Spreader) {
		TargetValue = Spreader->GetCurrentSpread();
		UE_LOG(LogTemp, Display, TEXT("Successful Spreader"));
	}
	else {
		TargetValue = 0.0f;
	}

	SpreadValue = FMath::FInterpTo(SpreadValue, TargetValue, InDeltaTime, SpreadInterpSpeed);
}
