// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacterA.h"
#include "EnemyCharacter.h"
#include "TPSController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DisplayWidgetComp.h"

ATPSGameMode::ATPSGameMode()
{
	VictoryWidgets = CreateDefaultSubobject<UDisplayWidgetComp>(TEXT("VictoryWidgets"));
	LoseWidgets = CreateDefaultSubobject<UDisplayWidgetComp>(TEXT("LoseWidgets"));
}

void ATPSGameMode::CharacterDied(AActor* DeadCharacter)
{
	if (DeadCharacter == MainCharacter) {
		MainCharacter->HandleDestruction();
		if (InputController) {
			InputController->SetInputEnabledState(false);
			LoseWidgets->ShowWidget();
		}
		// Gameover Function

		GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &ATPSGameMode::RestartLevel, 5.0f, false);
	}
	else if (AEnemyCharacter* DeadEnemy = Cast<AEnemyCharacter>(DeadCharacter)) {
		DeadEnemy->HandleDestruction();

		AController* EnemyController = DeadEnemy->GetController();
		if (EnemyController) {
			EnemyController->UnPossess();
		}

		EnemyCount--;
		if (EnemyCount == 0) {
			// 게임 종료 함수
			// 아래는 테스트용 함수
			//UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
			VictoryWidgets->ShowWidget();
			GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &ATPSGameMode::RestartLevel, 5.0f, false);
		}
	}
}

void ATPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATPSGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

int ATPSGameMode::GetEnemyCount()
{
	TArray<AActor*> Enemys;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyCharacter::StaticClass(), Enemys);

	return Enemys.Num();
}

void ATPSGameMode::HandleGameStart()
{
	EnemyCount = GetEnemyCount();

	MainCharacter = Cast<AMainCharacterA>(UGameplayStatics::GetPlayerPawn(this, 0));
	InputController = Cast<ATPSController>(UGameplayStatics::GetPlayerController(this, 0));
	// Gamestart Function
	if (InputController) {
		InputController->SetInputEnabledState(true);
	}
}


