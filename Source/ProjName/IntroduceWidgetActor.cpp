// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroduceWidgetActor.h"
#include "Components/BoxComponent.h"
#include "DisplayWidgetComp.h"
#include "MainCharacterA.h"

// Sets default values
AIntroduceWidgetActor::AIntroduceWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Area"));
	WidgetArea->SetupAttachment(RootComponent);

	WidgetComp = CreateDefaultSubobject<UDisplayWidgetComp>(TEXT("WidgetComp"));
}

// Called when the game starts or when spawned
void AIntroduceWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	WidgetArea->OnComponentBeginOverlap.AddDynamic(this, &AIntroduceWidgetActor::OnBeginOverlap);
	WidgetArea->OnComponentEndOverlap.AddDynamic(this, &AIntroduceWidgetActor::OnEndOverlap);
}

// Called every frame
void AIntroduceWidgetActor::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);

}

void AIntroduceWidgetActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacterA* Player = Cast<AMainCharacterA>(OtherActor);
	if (Player) {
		WidgetComp->ShowWidget();
	}
}

void AIntroduceWidgetActor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacterA* Player = Cast<AMainCharacterA>(OtherActor);
	if (Player) {
		WidgetComp->HideWidget();
	}
}

