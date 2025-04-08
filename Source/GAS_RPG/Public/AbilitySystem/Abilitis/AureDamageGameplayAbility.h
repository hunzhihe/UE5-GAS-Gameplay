// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AureRPGAbilityTypes.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AureDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureDamageGameplayAbility : public UAureGameplayAbility
{
	GENERATED_BODY()
public:
	//触发伤害的事件
	UFUNCTION(BlueprintCallable)
	void ExecuteDamageEffect(AActor* Target);

	//创建技能负面效果使用的结构体
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

	//伤害效果
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;



protected:


	// //多类型伤害效果
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	// TMap<FGameplayTag,FScalableFloat> DamageTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;
	//负面效果伤害类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DeBuffDamageType = FGameplayTag();

	//触发负面的几率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DeBuffChance = 20.f;

	//负面伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DeBuffDamage = 5.f;

	//负面伤害触发间隔时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DeBuffFrequency = 1.f;

	//负面效果持续时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DeBuffDuration = 5.f;

	//死亡时，收到的冲击数值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DeathImpulseMagnitude = 60.f;

	//技能或者攻击击中敌人后，敌人受到的击退的力度
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float KnockbackForceMagnitude = 100.f;
	//触发击退的概率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float KnockbackChance = 0.f;


	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;


	

	
};
