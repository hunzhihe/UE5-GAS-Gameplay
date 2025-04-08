// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/AureGameplayAbility.h"

#include "AbilitySystem/AureAttributeSet.h"

void UAureGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UAureGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

FString UAureGameplayAbility::GetDescription(int32 Level)
{
	return FString :: Printf(TEXT("%s,<Level>%d</>"),L"默认技能名称 - 火球术",Level);
}

FString UAureGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("下一等级：<Level>%d</>造成更多伤害。"),Level);
}

FString UAureGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("技能将在角色达到<Level>%d</>级时解锁。"),Level);
}

float UAureGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	//获取到冷却GE
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		//遍历GE修改的内容
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
          //判断修改的属性是否为角色蓝量属性
          if (Mod.Attribute == UAureAttributeSet::GetMonaAttribute())
          {
	          //通过修饰符获取到使用的FScalableFloat并计算传入等级的蓝量消耗，FScalableFloat是受保护性的属性，无法直接获取，只能通过函数
          	  Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel,ManaCost);
          	  break;//获取到了就结束遍历
          }
		}
	}
	return ManaCost;
}

float UAureGameplayAbility::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;
	//获取到技能冷却GE
	if (const UGameplayEffect* CooldownEffect = GetCostGameplayEffect())
	{
		//获取到当前冷却时间
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel,Cooldown);
	}
	return Cooldown;
}

