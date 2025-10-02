// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */

class UBehaviorTree;

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
};
