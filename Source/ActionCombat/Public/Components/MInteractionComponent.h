
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	void PrimaryInteract();

	UMInteractionComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
