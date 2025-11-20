// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DisplayWidgetComp.generated.h"

class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJNAME_API UDisplayWidgetComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDisplayWidgetComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ShowWidget();

	UFUNCTION()
	void HideWidget();
private:
	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<UUserWidget> Widgets;

	UPROPERTY()
	UUserWidget* DisplayedWidget;
};
