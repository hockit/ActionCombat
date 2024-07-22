
#include "Weapons/MMartialArts.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "./Components/MAttributeComponent.h"

AMMartialArts::AMMartialArts()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMMartialArts::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMMartialArts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMMartialArts::StartAttack_Implementation(FName BoneStart, FName BoneEnd)
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector StartTrace = MyCharacter->GetMesh()->GetSocketLocation(BoneStart);
	FVector EndTrace = MyCharacter->GetMesh()->GetSocketLocation(BoneEnd);
	float Radius = 15.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MyCharacter);
	ActorsToIgnore.Add(GetInstigator());

	FHitResult HitResult;

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartTrace, EndTrace, Radius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);


	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(HitActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
			if (AttributeComp)
			{
				AttributeComp->ApplyHealthChange(-20.f);
			}
		}
	}
}
