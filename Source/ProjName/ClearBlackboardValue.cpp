// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UClearBlackboardValue::UClearBlackboardValue()
{
	NodeName = "ClearBlackboardValue";

}

EBTNodeResult::Type UClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
