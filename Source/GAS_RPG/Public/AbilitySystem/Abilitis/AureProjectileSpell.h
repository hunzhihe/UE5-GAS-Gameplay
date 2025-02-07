// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "AureProjectileSpell.generated.h"

class AAureProjectile;
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureProjectileSpell : public UAureGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//抛射物类
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAureProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable, Category = "Ability|Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	//伤害效果
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
