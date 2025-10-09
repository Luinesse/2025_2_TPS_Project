// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */

class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

struct FAIStimulus;

UCLASS()
class PROJNAME_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyController();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* MyBehavior;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AIPerception;

	UAISenseConfig_Sight* SightConfig;
	UAISenseConfig_Hearing* HearingConfig;
	UAISenseConfig_Damage* DamageConfig;

private:
	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
