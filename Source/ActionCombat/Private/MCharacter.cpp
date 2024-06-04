
#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/MInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Weapons/MMartialArts.h"

AMCharacter::AMCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UMInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	bIsCombat = false;
	bAttackWindowOpen = false;
	DefaultBasicComboAttack = "Basic01";
}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetDefaultCombos();
	
	if (MartialArtsWeaponClass)
	{
		MartialArt = GetWorld()->SpawnActor<AMMartialArts>(MartialArtsWeaponClass);
	}
}

void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMCharacter::Walk);
	PlayerInputComponent->BindAction("Equip", EInputEvent::IE_Pressed, this, &AMCharacter::SwitchCombat);
	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", EInputEvent::IE_Pressed, this, &AMCharacter::PrimaryInteract);
}

void AMCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0;
	ControlRot.Roll = 0.0;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AMCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0;
	ControlRot.Roll = 0.0;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void AMCharacter::Sprint()
{
	if (!bIsCombat)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void AMCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

//	--START-- Attack functions
void AMCharacter::SwitchCombat()
{
	if (!bIsCombat)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		bIsCombat = true;
	}
	else
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bIsCombat = false;
	}
}

void AMCharacter::PrimaryAttack()
{
	bool bMontagePlaying = GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
	if ((bAttackWindowOpen || !bMontagePlaying) && bIsCombat)
	{
		PlayAnimMontage(BasicComboMontage, 1.f, BasicComboAttack);
	}
}

void AMCharacter::SetDefaultCombos()
{
	BasicComboAttack = DefaultBasicComboAttack;
	bAttackWindowOpen = false;
}

void AMCharacter::NextComboSegment(FName NextBasicCombo)
{
	BasicComboAttack = NextBasicCombo;
	bAttackWindowOpen = true;
}
//	--END-- Attack functions

void AMCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}