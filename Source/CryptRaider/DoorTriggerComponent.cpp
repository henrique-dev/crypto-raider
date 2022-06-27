// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerComponent.h"

// Sets default values for this component's properties
UDoorTriggerComponent::UDoorTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UDoorTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag("player1"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *Actor->GetActorLabel());
		}
	}

	KeyPressed = false;
}

void UDoorTriggerComponent::keyPressed()
{
	KeyPressed = true;
}