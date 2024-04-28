
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONCOMBAT_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	virtual void BeginPlay() override;

	void MoveForward(float Value);

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
