// 关于GAS系统的学习


#include "AbilitySystem/RPGAbilitySystemGlobals.h"

#include "AureRPGAbilityTypes.h"

FGameplayEffectContext* URPGAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAureRPGGameplayEffectContext();
}
