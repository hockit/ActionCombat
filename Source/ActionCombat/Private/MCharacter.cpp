
#include "MCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMCharacter::AMCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

}

void AMCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}