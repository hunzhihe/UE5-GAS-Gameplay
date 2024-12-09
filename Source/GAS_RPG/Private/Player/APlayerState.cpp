// 关于GAS系统的学习


#include "Player/APlayerState.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"

AAPlayerState::AAPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAureAbilitySystemComponentBase>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAureAttributeSet>("AttributeSet");
   SetNetUpdateFrequency(100.f);
	
}

UAbilitySystemComponent* AAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
