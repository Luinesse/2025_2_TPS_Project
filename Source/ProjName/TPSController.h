// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSController.generated.h"

/**
 * 
 */
UCLASS()
class PROJNAME_API ATPSController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetInputEnabledState(bool bInputEnabledValue);
};
