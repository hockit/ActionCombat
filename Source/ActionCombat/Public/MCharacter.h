
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UMInteractionComponent;
class UAnimMontage;
class AMMartialArts;

UCLASS()
class ACTIONCOMBAT_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMInteractionComponent* InteractionComp;

public:
	
	AMCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MartialArts")
	AMMartialArts* MartialArt;

	UPROPERTY(EditAnywhere, Category = "MartialArts")
	TSubclassOf<AMMartialArts> MartialArtsWeaponClass;

	void SetDefaultCombos();
	void NextComboSegment(FName NextBasicCombo);

protected:
	

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* BasicComboMontage;

	FName BasicComboAttack;
	FName DefaultBasicComboAttack;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCombat;

	bool bAttackWindowOpen;

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Sprint();
	void Walk();

	void SwitchCombat();
	void PrimaryAttack();
	void PrimaryInteract();
	

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
