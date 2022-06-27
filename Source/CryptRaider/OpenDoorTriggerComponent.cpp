// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorTriggerComponent.h"

// Sets default values for this component's properties
UOpenDoorTriggerComponent::UOpenDoorTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UOpenDoorTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("HERE"));
}