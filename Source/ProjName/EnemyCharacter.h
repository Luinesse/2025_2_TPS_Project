// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class AEnemyBullet;

/**
 * 
 */
UCLASS()
class PROJNAME_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void PossessedBy(AController* NewController) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AEnemyCharacter();

	UFUNCTION()
	void StartFireTimer();

	UFUNCTION()
	void StopFireTimer();
public:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AEnemyBullet> Bullet;
	
	UPROPERTY(EditAnywhere, Category = "Transform")
	USceneComponent* BulletPos;
private:
	void Fire() override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BulletSpreadAngle = 2.0f;

	FTimerHandle FireTimerHandle;
};
