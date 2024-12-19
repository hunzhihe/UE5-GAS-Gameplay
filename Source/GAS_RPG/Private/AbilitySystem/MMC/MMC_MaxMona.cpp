// 关于GAS系统的学习


#include "AbilitySystem/MMC/MMC_MaxMona.h"

UMMC_MaxMona::UMMC_MaxMona()
{
}

float UMMC_MaxMona::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Super::CalculateBaseMagnitude_Implementation(Spec);
}
