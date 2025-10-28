// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyBullet.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AEnemyController* MyController = Cast<AEnemyController>(NewController);
	if (MyController) {
		MyController->OnStartFireRequest.AddUObject(this, &AEnemyCharacter::StartFireTimer);
		MyController->OnStopFireRequest.AddUObject(this, &AEnemyCharacter::StopFireTimer);
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AEnemyCharacter::AEnemyCharacter()
{
	BulletPos = CreateDefaultSubobject<USceneComponent>(TEXT("BulletPos"));
	BulletPos->SetupAttachment(ACharacter::GetMesh(), TEXT("Muzzle_01"));
}

void AEnemyCharacter::StartFireTimer()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle)) {
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyCharacter::Fire, FireRate, true);
	}
}

void AEnemyCharacter::StopFireTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void AEnemyCharacter::Fire()
{
	if (Bullet) {
		AEnemyBullet* SpawnBullet = GetWorld()->SpawnActor<AEnemyBullet>(Bullet, BulletPos->GetComponentLocation(), BulletPos->GetComponentRotation());

		if (SpawnBullet) {
			SpawnBullet->SetOwner(this);
			SpawnBullet->FireInDirection(BulletPos->GetForwardVector());
		}

		if (FireSound) {
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}
