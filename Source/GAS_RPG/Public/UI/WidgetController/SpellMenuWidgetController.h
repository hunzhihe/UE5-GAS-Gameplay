// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AureGameplayTags.h"
#include "UI/WidgetController/AureWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

struct FAureGameplayTags;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointedEnabled, bool,
                                               bEquipEnabled, bool, bDemotionPointsEnabled,int32, Level);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FSpellDescriptionSignature, FString, Description, FString, NextLevelDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitForEquipSelectionSignature,const FGameplayTag&, InputTag,const FGameplayTag&,AbilityType);//等待技能装备选择
/**
 * 
 */
//在技能面板选中的技能的标签结构体
struct FSelectedAbility
{
	FGameplayTag AbilityTag = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
	int32 Level = 0;
};
UCLASS(BlueprintType, Blueprintable)
class GAS_RPG_API USpellMenuWidgetController : public UAureWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnPlayStateChangedSignature OnSpellPointChanged;
    //选中技能按钮后，升级和装备按钮的变动回调
	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature OnSpellGlobeSelectedSignature;
	//选中技能按钮后，生成描述
	UPROPERTY(BlueprintAssignable)
	FSpellDescriptionSignature SpellDescriptionSignature;
    //拖拽选中技能按钮后，广播可拖拽位置高亮显示
    FWaitForEquipSelectionSignature WaitForEquipSignature;
	
	//覆写两个基类函数，1.初始化广播数据，用于在创建时，显示角色当前的信息，2.在属性变动时委托广播
	virtual void BindCallbacksToDependencies() override;
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues() override;
	UFUNCTION(BlueprintCallable)
	int32 GetSpellPoints();

	//技能按钮选中调用函数，处理升级按钮和装配,通过传入技能标签，返回当前技能状态标签，通过标签，设置上锁的技能按钮，不会播放焦点动画
	UFUNCTION(BlueprintCallable)
	FGameplayTag SpellGlobeSelected(const FGameplayTag& AbilityTag);

	//设置选中技能默认值
	FSelectedAbility SelectedAbility = {
		FAureGameplayTags::Get().Abilities_None,
		FAureGameplayTags::Get().Abilities_Status_Locked,
	};
	//用于保存当前技能可分配的点数
	int32 CurrentSpellPoints = 0;

	//用于广播当前技能按钮升降级按钮状态和可装配状态
	void BroadcastSpellGlobeSelected();

	//升级按钮调用函数
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed(const FGameplayTag& AbilityTag);
	//降级按钮调用函数
	UFUNCTION(BlueprintCallable)
	void DemotionPointButtonPressed(const FGameplayTag& AbilityTag);
	//取消按钮选中处理
	UFUNCTION(BlueprintCallable)
	void GlobeDeselect();
    //装配技能按钮按下事件
	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);

	//装配技能按钮按下事件
	UFUNCTION(BlueprintCallable)
	void EquipDragStart();
	UFUNCTION(BlueprintCallable)
	void EquipDragEnd();
private:
    //通过技能状态标签和可分配技能点数类获取技能是否可以装配和技能是否可以升级
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatusTag,int32 SpellPoints,bool& bShouldEnableSpellPoints,bool& bShouldEnableEquip,bool& bShouldEnableDemotionPoints);
};
