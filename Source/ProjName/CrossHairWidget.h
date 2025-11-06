// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJNAME_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Spread")
	float SpreadValue;

private:
	float TargetValue;

	UPROPERTY(EditAnywhere, Category = "Spread")
	float SpreadInterpSpeed = 5.0f;
};
