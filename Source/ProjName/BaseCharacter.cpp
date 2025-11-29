// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
	ATPSGameMode* GameModePtr = Cast<ATPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (HealthComp && GameModePtr) {
		HealthComp->OnDeath.AddUObject(GameModePtr, &ATPSGameMode::CharacterDied);
	}
}

void ABaseCharacter::Fire()
{
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::HandleDestruction()
{

	UCapsuleComponent* CapsuleValue = GetCapsuleComponent();
	
	if (CapsuleValue) {
		CapsuleValue->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	USkeletalMeshComponent* MeshValue = GetMesh();
	if (MeshValue) {
		MeshValue->SetCollisionProfileName(TEXT("Ragdoll"));
		MeshValue->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, TEXT("spine_01"));
		MeshValue->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, TEXT("thigh_l"));
		MeshValue->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, TEXT("thigh_r"));
		MeshValue->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, TEXT("root"));
		MeshValue->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, TEXT("pelvis"));
	}
	
	bAlive = false;
}

