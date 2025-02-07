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
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Damage")
	FScalableFloat Damage;
	
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartupInputTag;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
};
