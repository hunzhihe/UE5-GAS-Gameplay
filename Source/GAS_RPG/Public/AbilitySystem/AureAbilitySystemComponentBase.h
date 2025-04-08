// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AureAbilitySystemComponentBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&)
DECLARE_MULTICAST_DELEGATE(FAbilityGiven)
DECLARE_DELEGATE_OneParam(FForEachAbility,const FGameplayAbilitySpec&);//单播委托，只绑定一个回调
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag&/*技能标签*/,const FGameplayTag&/*技能状态标签*/,const int32);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag&/*技能标签*/,const FGameplayTag&/*技能状态标签*/,const FGameplayTag&/*输入标签*/,const FGameplayTag&/*上一个输入标签*/);
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Server, Reliable)//服务器运行，装备技能, 传入技能标签和技能槽标签
	void ServerEquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& SlotTag);
    UFUNCTION(Client, Reliable)//客户端运行，装备技能
	void ClientEquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& Status, const FGameplayTag& SlotTag ,const FGameplayTag& PreviousSlot);

	//清楚技能装配插槽的技能
	void ClearSlot(FGameplayAbilitySpec* AbilitySpec);

	//根据输入标签，清除技能装配插槽的技能
	void ClearAbilitiesofSlot(const FGameplayTag& SlotTag);

	//判断当前技能实例是否处于目标技能装配插槽
	static bool AbilityHasSlot(FGameplayAbilitySpec* AbilitySpec,const FGameplayTag& SlotTag);


	
	//效果资产标签，
	FEffectAssetTags EffectAssetTags;
    //技能初始化应用后的回调委托
	FAbilityGiven AbilityGivenDelegate;
	//技能状态改变委托
	FAbilityStatusChanged AbilityStatusChangedDelegate;
	//技能装配插槽改变委托
	FAbilityEquipped AbilityEquippedDelegate;
    //初始化应用技能后，此值为true，用于记录当前是否被初始化完成
	bool bStartupAbilitiesGiven = false;
	//添加玩家能力（主动）
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//添加和应用玩家能力（被动）
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	
	//void AbilityInputTagPressed(FGameplayTag InputTag);
	//输入标签_按下
	void AbilityInputTagHeld(const  FGameplayTag& InputTag);
	//输入标签_松开
	void AbilityInputTagReleased(const  FGameplayTag& InputTag);
	//遍历技能，通过委托回调广播
	void ForEachAbility(const FForEachAbility& AbilityDelegate);

    //升级属性
	void UpgradeAttribute(const FGameplayTag& AttributeTag);
	//服务器升级属性
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	static FGameplayTag GetAbilityTagFormSpec(const FGameplayAbilitySpec& AbilitySpec);//获取技能标签
	static FGameplayTag GetInputTagFormSpec(const FGameplayAbilitySpec& InputSpec);//获取技能输入标签
    static FGameplayTag GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);//获取技能状态标签


	//通过技能标签获取技能实例
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	//根据角色等级更新技能数据状态
	void UpdateAbilityStatuses(int32 Level);

	//服务器运行，消耗技能点函数提升技能等级
	UFUNCTION(Server, Reliable)
	void SeverSpendSpellPoint(const FGameplayTag& AbilityTag);
	//服务器运行，降级技能等级返还技能点
	UFUNCTION(Server, Reliable)
	void SeverDemotionSpellPoint(const FGameplayTag& AbilityTag);

	//通过技能标签获取技能描述
	bool GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag,FString& OutDescription,FString& OutNextLevelDescription);
protected:
	//通知效果应用
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied (UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const ;

	//技能状态更新后回调
	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag,const FGameplayTag& StatusTag,const int32 AbilityLevel);
};
