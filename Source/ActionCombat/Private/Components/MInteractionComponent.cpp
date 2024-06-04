
#include "Components/MInteractionComponent.h"
#include "./Interfaces/MGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMInteractionComponent::UMInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMInteractionComponent::PrimaryInteract()
{
	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector EndTrace = EyeLocation + (EyeRotation.Vector() * 500.f);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TArray<FHitResult> OutHits;

	float Radius = 20.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(OutHits, EyeLocation, EndTrace, FQuat::Identity, ObjectQueryParams, Shape);
	
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UMGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IMGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 24, LineColor, false, 2.f);
	}

	DrawDebugLine(GetWorld(), EyeLocation, EndTrace, LineColor, false, 2.f, 2.f);
}