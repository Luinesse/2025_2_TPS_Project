// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterA.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


AMainCharacterA::AMainCharacterA()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	NiagaraLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Niagara"));
	NiagaraLocation->SetupAttachment(ACharacter::GetMesh(), TEXT("Muzzle_01"));
	
	
}

void AMainCharacterA::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AMainCharacterA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacterA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr) {
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacterA::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacterA::Look);
		Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMainCharacterA::OnSprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainCharacterA::ReleaseSprint);
		Input->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMainCharacterA::Fire);
	}
	
}

void AMainCharacterA::Move(const FInputActionInstance& Instance)
{
	FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainCharacterA::Look(const FInputActionInstance& Instance)
{
	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();

	if (Controller != nullptr) {
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AMainCharacterA::OnSprint()
{
	UCharacterMovementComponent* CM = GetCharacterMovement();
	if (CM != nullptr) {
		CM->MaxWalkSpeed = 285.0f;
	}
}

void AMainCharacterA::ReleaseSprint()
{
	UCharacterMovementComponent* CM = GetCharacterMovement();
	if (CM != nullptr) {
		CM->MaxWalkSpeed = 115.0f;
	}
}

void AMainCharacterA::Fire()
{
	if (!bCanFire)	return;

	Super::Fire();

	FVector Start = NiagaraLocation->GetComponentLocation();
	FVector End = Start + (NiagaraLocation->GetForwardVector() * 5500.0f);
	FHitResult HitResult;

	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);

	if (AttackCameraShake) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(AttackCameraShake);
	}

	if (HasHit) {
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 8, FColor::Green, false, 5.0f);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 5.0f, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
	}

	FireEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireSystem, NiagaraLocation->GetComponentLocation());

	if (FireSound) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireEffect) {
		FireEffect->Activate();
	}

	bCanFire = false;

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AMainCharacterA::ResetFire, 0.1f, false);
}

void AMainCharacterA::ResetFire()
{
	bCanFire = true;
	FireEffect->Deactivate();
}
