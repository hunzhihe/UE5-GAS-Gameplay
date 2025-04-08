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
	DOREPLIFETIME(AAPlayerState, XP);
	DOREPLIFETIME(AAPlayerState, AttributePoints);
	DOREPLIFETIME(AAPlayerState, SpellPoints);
}

UAbilitySystemComponent* AAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAPlayerState::AddToLevel(const int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAPlayerState::SetLevel(const int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAPlayerState::AddToAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAPlayerState::SetAttributePoints(int32 InAttributePoints)
{
	AttributePoints = InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAPlayerState::AddToSkillPoints(int32 InSkillPoints)
{
	SpellPoints += InSkillPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAPlayerState::SetSkillPoints(int32 InSkillPoints)
{
	SpellPoints = InSkillPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}


void AAPlayerState::OnRep_Level(int32 OldLevel) const
{
	//上面修改委托只会在服务器触发，在此处设置是在服务器更新到客户端本地化后触发
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAPlayerState::OnRep_XP(int32 OldXP) const
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AAPlayerState::OnRep_AttributePoints(int32 OldAttributePoints) const
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAPlayerState::OnRep_SpellPoints(int32 OldSpellPoints) const
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
