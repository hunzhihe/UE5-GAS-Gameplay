// 关于GAS系统的学习


#include "Player/APlayerState.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAPlayerState::AAPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAureAbilitySystemComponentBase>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAureAttributeSet>("AttributeSet");
   SetNetUpdateFrequency(100.f);
	
}

void AAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAPlayerState, Level);
}

UAbilitySystemComponent* AAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAPlayerState::OnRep_Level(int32 OldLevel) const
{
	
}
