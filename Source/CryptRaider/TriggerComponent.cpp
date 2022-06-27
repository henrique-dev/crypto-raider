// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMover();
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleWithOverlapActors();
	if (IsMovingToPedestal)
	{
		MoveToPedestal(DeltaTime);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");

		if (StartAttached || HasAcceptableTag && !IsGrabbed)
		{			
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover()
{
	if (ComponentToTrigger)
	{
		UActorComponent* Comp = ComponentToTrigger->FindComponentByClass<UMover>();
		if (Comp)
		{
			UMover* Component = Cast<UMover>(Comp);
			if (Component)
			{
				Mover = Component;
			}
		}
	}
}

void UTriggerComponent::MoveToPedestal(float DeltaTime)
{
	if (Mover != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(ActorToMove->GetRootComponent());

		if (Component != nullptr)
		{
			FVector ActorLocation = Component->GetComponentLocation();
			FRotator ActorRotation = Component->GetComponentRotation();

			FVector CurrentLocation = Component->GetComponentLocation();
			FVector TargetLocation = PedestalLocation;

			float Speed = FVector::Distance(OriginalActorLocation, TargetLocation) / 2;

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

			ActorToMove->SetActorLocation(NewLocation);
			ActorToMove->SetActorRotation(PedestalRotation);

			if (StartAttached || CurrentLocation.Equals(TargetLocation, 5))
			{
				// UE_LOG(LogTemp, Warning, TEXT("ABRINDO"));
				ActorToMove->SetActorLocation(TargetLocation);
				IsSomeObjectInPedestal = true;
				IsMovingToPedestal = false;
				Component->SetSimulatePhysics(false);
				ActorToMove->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
				Mover->SetShouldMove(true);
			}
		}
	}
}

void UTriggerComponent::HandleWithOverlapActors()
{
	for (USceneComponent* cmp : this->GetAttachChildren())
	{
		// UE_LOG(LogTemp, Warning, TEXT("tem um objeto"));
		return;
	}

	AActor* Actor = GetAcceptableActor();

	StartAttached = false;

	if (Actor != nullptr)
	{				
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			ActorToMove = Actor;
			IsMovingToPedestal = true;
			OriginalActorLocation = Component->GetComponentLocation();
		}		
	}	
	// UE_LOG(LogTemp, Warning, TEXT("nao tem um objeto"));
	Mover->SetShouldMove(false);
}