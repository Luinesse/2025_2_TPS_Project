// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSController.h"

void ATPSController::SetInputEnabledState(bool bInputEnabledValue)
{
	if (bInputEnabledValue) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}
}
