// 关于GAS系统的学习


#include "Character/AureEnemy.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "GAS_RPG/GAS_RPG.h"

AAureEnemy::AAureEnemy()
{
   GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAureAbilitySystemComponentBase>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);
   AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	
	AttributeSet = CreateDefaultSubobject<UAureAttributeSet>("AttributeSet");
}

void AAureEnemy::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAureEnemy::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAureEnemy::GetLevel()
{
	return Level;
}

void AAureEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
   InitAbilityActorInfo();
	
}

void AAureEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAureAbilitySystemComponentBase>(AbilitySystemComponent)->AbilityActorInfoSet();
}
