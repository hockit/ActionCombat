
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Interfaces/MWeaponInterface.h"
#include "MMartialArts.generated.h"

UCLASS()
class ACTIONCOMBAT_API AMMartialArts : public AActor, public IMWeaponInterface
{
	GENERATED_BODY()
	
public:	
	
	AMMartialArts();

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void StartAttack_Implementation(FName BoneStart, FName BoneEnd);
};
