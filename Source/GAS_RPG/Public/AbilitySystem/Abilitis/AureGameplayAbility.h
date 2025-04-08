// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AureGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
 //    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Damage")
	// FScalableFloat Damage;
	
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartupInputTag;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	//获取当前等级的技能描述
	virtual FString GetDescription(int32 Level);
	//获取技能下一等级的技能描述
	virtual FString GetNextLevelDescription(int32 Level);
	//获取锁定技能的描述
	static  FString GetLockedDescription(int32 Level);


protected:
	//获取技能蓝量消耗
	float GetManaCost(float InLevel = 1.f) const;
	//获取技能冷却时间
	float GetCooldown(float InLevel = 1.f) const;
};
