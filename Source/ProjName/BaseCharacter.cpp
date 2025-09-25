// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"

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
	// 노티파이를 통해 몽타주 종료 시 visibility off
	// tick off
	// 위 내용을 노티파이 구현부에서 작성

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
	
}

