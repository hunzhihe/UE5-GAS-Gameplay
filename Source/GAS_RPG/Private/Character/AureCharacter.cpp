// 关于GAS系统的学习


#include "Character/AureCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/APlayerState.h"

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

	//移动组件相关
	GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0, 400, 0);
    GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//移动组件相关结束
}

void AAureCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
    //服务器端
	InitAbilityActorInfo();
}

void AAureCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//客户端
	InitAbilityActorInfo();
}

void AAureCharacter::InitAbilityActorInfo()
{
	//服务器端和客户端的Init ability actor info
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	AurePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AurePlayerState,this);
	AbilitySystemComponent = AurePlayerState->GetAbilitySystemComponent();
	AttributeSet = AurePlayerState->GetAttributeSet();
}
