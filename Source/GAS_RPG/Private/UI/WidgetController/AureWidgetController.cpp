// 关于GAS系统的学习


#include "UI/WidgetController/AureWidgetController.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "Player/APlayerState.h"
#include "Player/AurePlayerController.h"

void UAureWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController=WidgetControllerParams.PlayerController;
	
	PlayerState = WidgetControllerParams.PlayerState;
	
	AbilitySystemComponent=WidgetControllerParams.AbilitySystemComponent;
	AttributeSet=WidgetControllerParams.AttributeSet;
}

void UAureWidgetController::BroadcastInitialValues()
{
	
}

void UAureWidgetController::BindCallbacksToDependencies()
{
	
}

void UAureWidgetController::BroadcastAbilityInfo()
{
	if (!GetAureAbilitySystemComponent()->bStartupAbilitiesGiven) return;
	//创建单薄委托
	FForEachAbility BroadcastDelegate;
	//创建绑定回调匿名函数，委托广播时将会出发函数内部逻辑
	BroadcastDelegate.BindLambda(
		[this](const FGameplayAbilitySpec& AbilitySpec)
		{
			//UE_LOG(LogTemp, Warning, TEXT("AbilitySpec.Ability->GetInstancingPolicy() = %d"), AbilitySpec.Ability->GetInstancingPolicy());
			//通过静态函数获取到技能实例的技能标签
			FAureAbilityInfo Info = AbilityInfo->GetAbilityInfoByTag(AureAbilitySystemComponent->GetAbilityTagFormSpec(AbilitySpec));
			//获取到技能的输入标签
			Info.InputTag = AureAbilitySystemComponent->GetInputTagFormSpec(AbilitySpec);
			//获取技能的状态标签
			Info.StatusTag = AureAbilitySystemComponent->GetStatusTagFromSpec(AbilitySpec);

			//广播技能数据
			OnAbilityInfoDelegate.Broadcast(Info);
		}
	);
	//遍历技能并触发委托回调
	GetAureAbilitySystemComponent()->ForEachAbility(BroadcastDelegate);
}

void UAureWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag,
	const FGameplayTag& SlotTag, const FGameplayTag& PreviousSlot)
{
	const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
	//清除修插槽数据
	FAureAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	OnAbilityInfoDelegate.Broadcast(LastSlotInfo);

	//更新新插槽的数据
	FAureAbilityInfo NewSlotInfo = AbilityInfo->GetAbilityInfoByTag(AbilityTag);
	NewSlotInfo.StatusTag = StatusTag;
	NewSlotInfo.InputTag = SlotTag;
	OnAbilityInfoDelegate.Broadcast(NewSlotInfo);
}

AAurePlayerController* UAureWidgetController::GetAurePlayerController()
{
	if (AurePlayerController==nullptr)
	{
		AurePlayerController = Cast<AAurePlayerController>(PlayerController);
	}
	return AurePlayerController;
}

AAPlayerState* UAureWidgetController::GetAurePlayerState()
{
	if (AurePlayerState==nullptr)
	{
		AurePlayerState = Cast<AAPlayerState>(PlayerState);
	}
	return AurePlayerState;
}

UAureAbilitySystemComponentBase* UAureWidgetController::GetAureAbilitySystemComponent()
{
	if (AureAbilitySystemComponent==nullptr)
	{
		AureAbilitySystemComponent = Cast<UAureAbilitySystemComponentBase>(AbilitySystemComponent);
	}
	return AureAbilitySystemComponent;
}

UAureAttributeSet* UAureWidgetController::GetAureAttributeSet()
{
	if (AureAttributeSet==nullptr)
	{
		AureAttributeSet = Cast<UAureAttributeSet>(AttributeSet);
	}
	return AureAttributeSet;
}
