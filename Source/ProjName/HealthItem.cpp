// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"
#include "MainCharacterA.h"
#include "HealthComponent.h"

// Sets default values
AHealthItem::AHealthItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthPack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asset"));
	HealthPack->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthItem::BeginPlay()
{
	Super::BeginPlay();
	
	HealthPack->OnComponentHit.AddDynamic(this, &AHealthItem::OnHit);
}

// Called every frame
void AHealthItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMainCharacterA* IsMain = Cast<AMainCharacterA>(OtherActor);

	if (IsMain) {
		IsMain->HealthComp->SetHealth(0.1f);
		Destroy();
	}
}

