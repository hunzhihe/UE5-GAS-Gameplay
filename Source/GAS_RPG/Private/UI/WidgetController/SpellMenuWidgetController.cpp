// 关于GAS系统的学习


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include <Windows.UI.h>

#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "Player/APlayerState.h"

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	//绑定技能状态修改后的委托回调
	GetAureAbilitySystemComponent()->AbilityStatusChangedDelegate.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, const int32 Level)
	{
		//技能状态修改，修改技能的升降级按钮的状态
		if (SelectedAbility.AbilityTag.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;

			SelectedAbility.Level = Level;
			//广播技能状态
			BroadcastSpellGlobeSelected();
		}
		
		if (AbilityInfo)
		{
			//获取到技能数据
			FAureAbilityInfo Info = AbilityInfo->GetAbilityInfoByTag(AbilityTag);
			Info.StatusTag = StatusTag;
			OnAbilityInfoDelegate.Broadcast(Info);
		}
	}
	);
	//绑定技能点变化的委托回调
	GetAurePlayerState()->OnSpellPointsChangedDelegate.AddLambda([this](const int32 SpellPoints)
	{
		//广播所拥有的技能点
		OnSpellPointChanged.Broadcast(SpellPoints);
		CurrentSpellPoints = SpellPoints;
		BroadcastSpellGlobeSelected();
	});

	//监听技能装配的回调
	GetAureAbilitySystemComponent()->AbilityEquippedDelegate.AddUObject(this,&USpellMenuWidgetController::OnAbilityEquipped);
}

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
    //广播所拥有的技能点
	OnSpellPointChanged.Broadcast(GetAurePlayerState()->GetSkillPoints()); 
}

int32 USpellMenuWidgetController::GetSpellPoints()
{
	return GetAurePlayerState()->GetSkillPoints();
}

FGameplayTag USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	//const int32 SpellPoint = GetSpellPoints();
	FGameplayTag AbilityStatus;
    //判断传入的标签是否存在
	const bool bTagValid = AbilityTag.IsValid();
	//判断标签是否为None技能标签
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	//通过技能标签获取到技能
    const FGameplayAbilitySpec* AbilitySpec = GetAureAbilitySystemComponent()->GetSpecFromAbilityTag(AbilityTag);
    //判断技能实例是否存在
	const bool bSpecValid = AbilitySpec !=nullptr;
	if (!bTagValid||bTagNone||!bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		//从技能实例处获取技能的状态标签
		AbilityStatus = GetAureAbilitySystemComponent()->GetStatusTagFromSpec(*AbilitySpec);
		SelectedAbility.Level = AbilitySpec->Level;
	}

	SelectedAbility.AbilityTag = AbilityTag;
    SelectedAbility.Status = AbilityStatus;
	CurrentSpellPoints = GetSpellPoints();

	BroadcastSpellGlobeSelected();
	return AbilityStatus; 
}

void USpellMenuWidgetController::BroadcastSpellGlobeSelected() 
{
	bool bEnableSpeedPoints = false;//技能是否可以升级
	bool bEnableEquip = false;//技能是否可以装配
	bool bEnableDemotion = false;//技能是否可以降级

	ShouldEnableButtons(SelectedAbility.Status,CurrentSpellPoints,bEnableSpeedPoints,bEnableEquip,bEnableDemotion);
	OnSpellGlobeSelectedSignature.Broadcast(bEnableSpeedPoints,bEnableEquip,bEnableDemotion,SelectedAbility.Level);

	//广播技能描述
	FString Description;
	FString NextLevelDescription;
	GetAureAbilitySystemComponent()->GetDescriptionByAbilityTag(SelectedAbility.AbilityTag,Description,NextLevelDescription);
	SpellDescriptionSignature.Broadcast(Description,NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed(const FGameplayTag& AbilityTag)
{
	if (GetAureAbilitySystemComponent())
	{
		//调用技能升级函数
		GetAureAbilitySystemComponent()->SeverSpendSpellPoint(AbilityTag);
	}
}

void USpellMenuWidgetController::DemotionPointButtonPressed(const FGameplayTag& AbilityTag)
{
	if (GetAureAbilitySystemComponent())
	{
		//调用技能降级函数
		GetAureAbilitySystemComponent()->SeverDemotionSpellPoint(AbilityTag);
	}
}

void USpellMenuWidgetController::GlobeDeselect()
{
	//重置缓存内容，并广播清空技能描述的内容
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	SelectedAbility.AbilityTag = GameplayTags.Abilities_None;
	SelectedAbility.Status = GameplayTags.Abilities_Status_Locked;
	SelectedAbility.Level = 0;

	SpellDescriptionSignature.Broadcast(FString(),FString());
	
}

void USpellMenuWidgetController::EquipButtonPressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	//获取装配技能的类型
	const FGameplayTag& SelectedAbilityTypeTag = AbilityInfo->GetAbilityInfoByTag(SelectedAbility.AbilityTag).AbilityType;
	if (!SelectedAbilityTypeTag.MatchesTagExact(AbilityType))
	{
		return;//不匹配
	}
	//获取装配技能的输入标签
	const FGameplayTag& SelectedAbilityInputTag = AbilityInfo->GetAbilityInfoByTag(SelectedAbility.AbilityTag).InputTag;
	if (SelectedAbilityInputTag.MatchesTagExact(SlotTag)) return;//如果当前技能输入和插槽标签相等，证明已经装配，无需处理
	
		//调用技能装配函数
	GetAureAbilitySystemComponent()->ServerEquipAbility(SelectedAbility.AbilityTag,SlotTag);
	
	
}

void USpellMenuWidgetController::EquipDragStart()
{
	const FAureAbilityInfo Info = AbilityInfo->GetAbilityInfoByTag(SelectedAbility.AbilityTag);
	const FGameplayTag& SelectedAbilityInputTag =
		GetAureAbilitySystemComponent()->GetInputTagFormSpec(*GetAureAbilitySystemComponent()->GetSpecFromAbilityTag(SelectedAbility.AbilityTag));
	WaitForEquipSignature.Broadcast(SelectedAbility.AbilityTag,SelectedAbilityInputTag);
}

void USpellMenuWidgetController::EquipDragEnd()
{
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	WaitForEquipSignature.Broadcast(GameplayTags.Abilities_None,GameplayTags.Abilities_None);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatusTag, const int32 SpellPoints,
                                                     bool& bShouldEnableSpellPoints, bool& bShouldEnableEquip, bool& bShouldEnableDemotionPoints)
{
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	//锁定
	if (AbilityStatusTag.MatchesTag(GameplayTags.Abilities_Status_Locked))
	{
		bShouldEnableEquip = false;
		bShouldEnableSpellPoints = false;
		bShouldEnableDemotionPoints = false;
	}
	//解锁
	else if (AbilityStatusTag.MatchesTag(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquip = true;
		if (SpellPoints>0)
		{
			bShouldEnableSpellPoints = true;
		}
		bShouldEnableDemotionPoints = true;
	}
	//装备
	else if (AbilityStatusTag.MatchesTag(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquip = true;
		if (SpellPoints>0)
		{
			bShouldEnableSpellPoints = true;
		}
		bShouldEnableDemotionPoints =true;
	}
	//可解锁
	else if (AbilityStatusTag.MatchesTag(GameplayTags.Abilities_Status_Eligible))
	{
		bShouldEnableEquip = false;
		if (SpellPoints>0)
		{
			bShouldEnableSpellPoints = true;
		}
		bShouldEnableDemotionPoints = false;
	}
	
}
 