// 关于GAS系统的学习


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "Player/APlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetAureAttributeSet()->GetShengMingZhi());
	OnMaxHealthChanged.Broadcast(GetAureAttributeSet()->GetMaxShengMingZhi());
	
	OnManaChanged.Broadcast(GetAureAttributeSet()->GetMona());
	OnMaxManaChanged.Broadcast(GetAureAttributeSet()->GetMaxMona());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//AAPlayerState* AurePlayerState = CastChecked<AAPlayerState>(PlayerState);
	//绑定等级相关回调
	GetAurePlayerState()->OnXPChangedDelegate.AddUObject(this,&ThisClass::OnXPChanged);
	GetAurePlayerState()->OnLevelChangedDelegate.AddLambda([this](int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	//const UAureAttributeSet* AureAttributeSet = CastChecked<UAureAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAureAttributeSet()->GetShengMingZhiAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{

			OnHealthChanged.Broadcast(Data.NewValue);
		});


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAureAttributeSet()->GetMaxShengMingZhiAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAureAttributeSet()->GetMonaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnManaChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAureAttributeSet()->GetMaxMonaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnMaxManaChanged.Broadcast(Data.NewValue);
	});
	

	if (GetAureAbilitySystemComponent())
	{
		if (GetAureAbilitySystemComponent()->bStartupAbilitiesGiven)
		{
			//若执行到此处，则技能的初始化已经完成，则直接调用初始化回调
			BroadcastAbilityInfo();
		}
		else
		{
			//技能初始化未完成，将通过绑定委托，监听广播的形式触发初始化完成回调
			GetAureAbilitySystemComponent()->AbilityGivenDelegate.AddUObject(this,&ThisClass::BroadcastAbilityInfo);
			
		}
	}
    
	

	GetAureAbilitySystemComponent()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{

				//Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")));
				//对标签检测，如果不是信息标签，则直接返回，不广播
				if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
					if (Row != nullptr)
					{
						OnMessageWidgetRowDelegate.Broadcast(*Row);
					}
                    //OnMessageWidgetRowDelegate.Broadcast(*Row);
				}
				// const FString Msg = FString::Printf(TEXT("Overlay Widget Controller: %s"), *Tag.ToString());
				// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, Msg);
				
			}
		}
		);
	GetAureAbilitySystemComponent()->AbilityEquippedDelegate.AddUObject(this,&ThisClass::OnAbilityEquipped);
	
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	ULevelUpInfo* LevelUpInfo = GetAurePlayerState()->LevelUpInfo;
	checkf(LevelUpInfo,TEXT("无法查询到等级相关数据，请查看PlayState是否设置了对应的数据"));

	//获取当前等级
	const int32 Level = LevelUpInfo->FindLeveForXP(NewXP);
	//获取当前最大等级
	const int32 MaxLevel = LevelUpInfo->LevelUpInfomation.Num();

	if (Level<=MaxLevel && Level>0)
	{
		//获取当前等级升级所需经验值
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level].LevelUpRequirement;
		//获取上一级升级所需经验值
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level-1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;
		const float XPPercent = static_cast<float>(XPForThisLevel)/static_cast<float> (DeltaLevelRequirement);
		//广播经验条
		OnXPPercentChangeDelegate.Broadcast(XPPercent);
	}
}

