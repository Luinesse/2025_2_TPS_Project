// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireTask.h"
#include "EnemyController.h"

EBTNodeResult::Type UEnemyFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	if (AIController) {
		AIController->OnStartFireRequest.Broadcast();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
