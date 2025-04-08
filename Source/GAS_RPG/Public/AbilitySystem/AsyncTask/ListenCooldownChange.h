// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ListenCooldownChange.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChange,float,TimeRemaining);
/**
 * 
 */
UCLASS(BlueprintType,meta = (ExposedAsyncProxy="AsyncTask"))
class GAS_RPG_API UListenCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	//技能冷却触发开始委托
	UPROPERTY(BlueprintAssignable)
	FCooldownChange CooldownStart;
	//技能冷却触发结束委托
	UPROPERTY(BlueprintAssignable)
	FCooldownChange CooldownEnd;

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly="true"))
	static UListenCooldownChange* ListenCooldownChange(UAbilitySystemComponent* AbilitySystemComponent,FGameplayTag InCooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

    //监听冷却标签回调函数
	void CooldownTagChanged(const FGameplayTag InCooldownTag,int32 NewCount);
	//监听ASC激活GE的回调
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;
};
