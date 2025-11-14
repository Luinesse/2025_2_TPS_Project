// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJNAME_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void CalculateHealth(float Health, float MaxHealth);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Variable")
	float HealthPercent;
};
