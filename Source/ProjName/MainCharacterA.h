// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacterA.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class PROJNAME_API AMainCharacterA : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMainCharacterA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

protected:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void OnSprint();
	void ReleaseSprint();
private:
	UPROPERTY(EditAnywhere, Category = "View")
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	bool bCanFire = true;
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Effect")
	USceneComponent* NiagaraLocation;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* FireSystem;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraComponent* FireEffect;

	void Fire() override;
	void ResetFire();
};
