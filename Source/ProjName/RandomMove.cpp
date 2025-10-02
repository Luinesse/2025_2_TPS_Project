#include "RandomMove.h"
#include "EnemyCharacter.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

URandomMove::URandomMove()
{
	NodeName = "Random Move";

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(URandomMove, BlackboardKey));
}

EBTNodeResult::Type URandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* MyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (MyCharacter) {
		FVector Locate = MyCharacter->GetActorLocation();
		FNavLocation NavLocate;

		if (UNavigationSystemV1::GetNavigationSystem(GetWorld())->GetRandomReachablePointInRadius(Locate, SearchRadius, NavLocate)) {
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocate.Location);

			UE_LOG(LogTemp, Display, TEXT("Succeded"));

			return EBTNodeResult::Succeeded;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Failed"));

	return EBTNodeResult::Failed;
}
