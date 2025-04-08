// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/AureDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "Interaction/CombatInterface.h"

void UAureDamageGameplayAbility::ExecuteDamageEffect(AActor* Target)
{
	//创建GE
    //FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass,1.f);
	FDamageEffectParams Params = MakeDamageEffectParamsFromClassDefaults(Target);

	//设置死亡冲击和击退
	if (IsValid(Target))
	{
		//获取攻击对象和目标朝向，并专函角度
		FRotator TargetRotation = Target->GetActorRotation();
		TargetRotation.Pitch = 45.f;
		const FVector TargetDirection = TargetRotation.Vector();
		Params.DeathImpulse = TargetDirection * Params.DeathImpulseMagnitude;
		//判断攻击是否触发击退
		if (FMath::RandRange(1,100)<Params.KnockbackChance)
		{
			Params.KnockbackForceDirection = TargetDirection * KnockbackForceMagnitude;
		}
	}

	//将GE应用到目标
	UAureAbilitySysTEM_BFL::ApplyDamageEffect(Params);
}

FTaggedMontage UAureDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 SelectedMontageIndex = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[SelectedMontageIndex];
	}
	return FTaggedMontage();
}

FDamageEffectParams UAureDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor) const
{
    FDamageEffectParams Params;
	Params.WorkContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceASC = GetAbilitySystemComponentFromActorInfo();
	Params.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;
	
	Params.DeBuffChance = DeBuffChance;
	Params.DeBuffDamage = DeBuffDamage;
	Params.DeBuffDuration = DeBuffDuration;
	Params.DeBuffFrequency = DeBuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockbackForceMagnitude = KnockbackForceMagnitude;
	Params.KnockbackChance = KnockbackChance;
	return Params;
}


