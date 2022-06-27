// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerComponent.h"
#include "OpenDoorTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UOpenDoorTriggerComponent : public UTriggerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoorTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	
};
