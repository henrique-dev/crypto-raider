// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("We dont have a componet"));
		return;
	}

	UPrimitiveComponent* HitComponent = PhysicsHandle->GetGrabbedComponent();

	if (HitComponent != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + (GetForwardVector() * HoldDistance);
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabber::Grab()
{
	SweepObject();
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("We dont have a componet"));
		return;
	}

	UPrimitiveComponent* HitComponent = PhysicsHandle->GetGrabbedComponent();

	if (HitComponent != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
		HitComponent->GetOwner()->Tags.Remove(FName("Grabbed"));
	}
}

void UGrabber::SweepObject()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("We dont have a componet"));
		return;
	}

	FHitResult HitResult;

	if (GetGrabbableInReach(HitResult))
	{		
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		HitComponent->SetSimulatePhysics(true);
		HitComponent->DetachFromParent(true);

		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add(FName("Grabbed"));
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabberRadius);
	FVector Start = GetComponentLocation();
	FVector End = Start + (MaxGrabberDistance * GetForwardVector());

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	bool HasHitSomething = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	if (HasHitSomething)
	{
		DrawDebugSphere(GetWorld(), OutHitResult.Location, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		FString ActorNameOrLabel = OutHitResult.GetActor()->GetActorNameOrLabel();		
		return true;
	}
	return false;
}