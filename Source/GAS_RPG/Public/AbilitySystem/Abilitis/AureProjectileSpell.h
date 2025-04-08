// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AureDamageGameplayAbility.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "AureProjectileSpell.generated.h"

class AAureProjectile;
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureProjectileSpell : public UAureDamageGameplayAbility
{
	GENERATED_BODY()


public:
	//获取投射技能的描述
	virtual FString GetDescription(int32 Level) override;
	//获取投射技能下一等级的描述
	virtual FString GetNextLevelDescription(int32 Level) override;
	
	UPROPERTY()//场景组件，用于确定当前投掷物的攻击目标
	TObjectPtr<USceneComponent>HomingTargetSceneComponent;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//抛射物类
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAureProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable, Category = "Ability|Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation,const FGameplayTag& SocketTag,bool bOverridePitch, float PitchOverride);

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;

	//伤害效果
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//TSubclassOf<UGameplayEffect> DamageEffectClass;
};
