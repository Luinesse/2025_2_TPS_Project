// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthItem.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::GetHealth()
{
	return Health;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetHealth(float AddHealth)
{
	if (AddHealth < 0.0f)	return;

	if (Health + AddHealth >= MaxHealth) {
		Health = MaxHealth;
	}
	else {
		Health += AddHealth;
	}

	OnChangedHealthPercent.Broadcast(Health, MaxHealth);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("Execute AnyDamage ! Current HP : %f"), Health);

	OnChangedHealthPercent.Broadcast(Health, MaxHealth);

	if (Health <= 0) {
		OnDeath.Broadcast(DamagedActor);
	}
}
