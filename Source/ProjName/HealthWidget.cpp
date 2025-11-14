// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

void UHealthWidget::CalculateHealth(float Health, float MaxHealth)
{
	if (MaxHealth > 0) {
		HealthPercent = Health / MaxHealth;
	}
	else {
		HealthPercent = 0.0f;
	}
}
