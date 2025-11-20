// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameMode.generated.h"

/**
 * 
 */

class AMainCharacterA;
class ATPSController;
class UDisplayWidgetComp;

UCLASS()
class PROJNAME_API ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATPSGameMode();

	void CharacterDied(AActor* DeadCharacter);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UDisplayWidgetComp* VictoryWidgets;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UDisplayWidgetComp* LoseWidgets;

	AMainCharacterA* MainCharacter;
	ATPSController* InputController;

	int EnemyCount;
	int GetEnemyCount();

	void HandleGameStart();
};
