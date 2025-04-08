// 关于GAS系统的学习


#include "Character/AureCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	CameraBoon = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    CameraBoon->SetupAttachment(GetRootComponent());
    CameraBoon->SetUsingAbsoluteRotation(true);
	CameraBoon->bDoCollisionTest = false;
	

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Top Down Camera"));
	TopDownCameraComponent->SetupAttachment(CameraBoon, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	CharacterClass = ECharacterClass::Elementalist;

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
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

void AAureCharacter::AddToXP_Implementation(int32 InXP)
{
	AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	PlayerStateBase->AddToXP(InXP);
}

void AAureCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}
void AAureCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
        const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotator = (CameraLocation-NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotator);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AAureCharacter::GetXP_Implementation() const
{
	const AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	return PlayerStateBase->GetXP();
}

int32 AAureCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	return PlayerStateBase->LevelUpInfo->FindLeveForXP(InXP);
}

int32 AAureCharacter::GetAttributePoints_Implementation(int32 Level) const
{
	const AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	return PlayerStateBase->LevelUpInfo->LevelUpInfomation[Level].AttributePointAward;
}

int32 AAureCharacter::GetSkillPoints_Implementation(int32 Level) const
{
	const AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	return PlayerStateBase->LevelUpInfo->LevelUpInfomation[Level].SpellPointAward;
}

void AAureCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	//IPlayerInterface::AddToAttributePoints_Implementation(InAttributePoints);
	AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	PlayerStateBase->AddToAttributePoints(InAttributePoints);
}

void AAureCharacter::AddToSkillPoints_Implementation(int32 InSkillPoints)
{
	IPlayerInterface::AddToSkillPoints_Implementation(InSkillPoints);
	AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	PlayerStateBase->AddToSkillPoints(InSkillPoints);
}

void AAureCharacter::AddToPlayerLevel_Implementation(int32 InLevel)
{
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	AurePlayerState->AddToLevel(InLevel);


	if (UAureAbilitySystemComponentBase* AureASC = Cast<UAureAbilitySystemComponentBase>(GetAbilitySystemComponent()))
	{
		AureASC->UpdateAbilityStatuses(AurePlayerState->GetPlayerLevel());
	}
}

int32 AAureCharacter::GetAttributesPoints_Implementation() const
{
	const AAPlayerState* PlayerStateBase = GetPlayerState<AAPlayerState>();
	check(PlayerStateBase);
	return PlayerStateBase->GetAttributePoints();
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



int32 AAureCharacter::GetLevel_Implementation()
{
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	return AurePlayerState->GetPlayerLevel();
}

void AAureCharacter::InitAbilityActorInfo()
{
	//服务器端和客户端的Init ability actor info
	AAPlayerState* AurePlayerState = GetPlayerState<AAPlayerState>();
	check(AurePlayerState);
	//获取玩家状态
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

	OnAscRegistered.Broadcast(AbilitySystemComponent);
}


