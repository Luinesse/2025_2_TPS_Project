// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacterA.h"
#include "EnemyCharacter.h"
#include "TPSController.h"
#include "Kismet/KismetSystemLibrary.h"

void ATPSGameMode::CharacterDied(AActor* DeadCharacter)
{
	if (DeadCharacter == MainCharacter) {
		MainCharacter->HandleDestruction();
		if (InputController) {
			InputController->SetInputEnabledState(false);
		}
		// Gameover Function
	}
	else if (AEnemyCharacter* DeadEnemy = Cast<AEnemyCharacter>(DeadCharacter)) {
		DeadEnemy->HandleDestruction();
		EnemyCount--;
		if (EnemyCount == 0) {
			// ���� ���� �Լ�
			// �Ʒ��� �׽�Ʈ�� �Լ�
			UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
		}
	}
}

void ATPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
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


