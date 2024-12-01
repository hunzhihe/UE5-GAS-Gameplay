// 关于GAS系统的学习


#include "Character/AureCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAureCharacter::AAureCharacter()
{
 //    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
 //    SpringArm->SetupAttachment(RootComponent);
	// SpringArm->TargetArmLength =750;
	//
	// SpringArm->bUsePawnControlRotation = true;
 //
 //
 //    AureCamera = CreateDefaultSubobject<UCameraComponent>("Aure Camera");
	// AureCamera->SetupAttachment(SpringArm);
	// AureCamera->bUsePawnControlRotation = true;

	
	GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0, 400, 0);
    GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
