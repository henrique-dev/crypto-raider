// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

private:
	UPROPERTY(EditAnywhere)
		FName AcceptableActorTag;

	UPROPERTY(EditAnywhere)
		AActor* ComponentToTrigger;

	UPROPERTY(EditAnywhere)
		FVector PedestalLocation;

	UPROPERTY(EditAnywhere)
		FRotator PedestalRotation;

	UPROPERTY(EditAnywhere)
		bool StartAttached;

	bool IsSomeObjectInPedestal = false;
	bool IsMovingToPedestal = false;

	UMover* Mover;	
	AActor* ActorToMove;
	FVector OriginalActorLocation;

	void SetMover();
	AActor* GetAcceptableActor() const;
	void MoveToPedestal(float DeltaTime);
	void HandleWithOverlapActors();
	

};
