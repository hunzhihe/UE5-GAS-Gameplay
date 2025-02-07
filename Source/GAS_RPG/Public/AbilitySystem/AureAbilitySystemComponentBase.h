// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AureAbilitySystemComponentBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&)
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	

	//效果资产标签，
	FEffectAssetTags EffectAssetTags;

	//添加玩家能力
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//void AbilityInputTagPressed(FGameplayTag InputTag);
	//输入标签_按下
	void AbilityInputTagHeld(const  FGameplayTag& InputTag);
	//输入标签_松开
	void AbilityInputTagReleased(const  FGameplayTag& InputTag);
protected:
	//通知效果应用
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied (UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const ;
	
};
