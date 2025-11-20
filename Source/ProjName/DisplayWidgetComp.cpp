// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplayWidgetComp.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UDisplayWidgetComp::UDisplayWidgetComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDisplayWidgetComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDisplayWidgetComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDisplayWidgetComp::ShowWidget()
{
	if (Widgets && DisplayedWidget == nullptr) {
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC) {
			DisplayedWidget = CreateWidget<UUserWidget>(PC, Widgets);
			if (DisplayedWidget) {
				DisplayedWidget->AddToViewport();
			}
		}
	}
}

void UDisplayWidgetComp::HideWidget()
{
	if (DisplayedWidget) {
		DisplayedWidget->RemoveFromParent();
		DisplayedWidget = nullptr;
	}
}

