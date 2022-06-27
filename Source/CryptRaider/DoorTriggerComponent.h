// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerComponent.h"
#include "DoorTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UDoorTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UDoorTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable)
	void keyPressed();

	bool KeyPressed = false;
};
