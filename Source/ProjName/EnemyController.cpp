// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

AEnemyController::AEnemyController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.0f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 500.0f;
	HearingConfig->SetMaxAge(3.0f);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerception->ConfigureSense(*HearingConfig);

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	AIPerception->ConfigureSense(*DamageConfig);

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionUpdated);
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (MyBehavior) {
		RunBehaviorTree(MyBehavior);
		UE_LOG(LogTemp, Display, TEXT("Running"));
	}
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	const FAISenseID SenseID = Stimulus.Type;

	if (SenseID == UAISense::GetSenseID<UAISense_Sight>()) {
		if (Stimulus.WasSuccessfullySensed()) {
			// 시각 처리
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
		}
		else {
			// 시각에서 사라짐
			GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
		}
	}
	else if (SenseID == UAISense::GetSenseID<UAISense_Hearing>()) {
		if (Stimulus.WasSuccessfullySensed()) {
			// 청각 처리
			GetBlackboardComponent()->SetValueAsVector(TEXT("SoundLocation"), Stimulus.StimulusLocation);
		}
	}
	else if (SenseID == UAISense::GetSenseID<UAISense_Damage>()) {
		if (Stimulus.WasSuccessfullySensed()) {
			// 데미지 처리
			if (Actor) {
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
				GetBlackboardComponent()->SetValueAsVector(TEXT("SoundLocation"), Stimulus.StimulusLocation);
			}
			else {
				GetBlackboardComponent()->SetValueAsVector(TEXT("SoundLocation"), Stimulus.StimulusLocation);
			}
		}
	}
}