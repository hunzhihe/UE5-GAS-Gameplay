// 关于GAS系统的学习


#include "Character/AureCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "HUD/AureHUD.h"
#include "Player/APlayerState.h"
#include "Player/AurePlayerController.h"

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
	//AddCharacterAbilities()
	InitializeAbilities();
}

void AAureCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//客户端
	InitAbilityActorInfo();
}

int32 AAureCharacter::GetLevel()
{
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	return AurePlayerState->GetLevel();
}

void AAureCharacter::InitAbilityActorInfo()
{
	//服务器端和客户端的Init ability actor info
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	AurePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AurePlayerState,this);
    Cast<UAureAbilitySystemComponentBase>(AurePlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	AbilitySystemComponent = AurePlayerState->GetAbilitySystemComponent();
	AttributeSet = AurePlayerState->GetAttributeSet();

	  if (AAurePlayerController* AurePlayerController = Cast<AAurePlayerController>(GetController()))
	  {
		  if (AAureHUD* AureHUD = Cast<AAureHUD>(AurePlayerController->GetHUD()))
		  {
			  AureHUD->InitOverlayWidget(AurePlayerController,AurePlayerState,AbilitySystemComponent,AttributeSet);
		  }
	  }
	InitializeDefaultAttributes();
}
