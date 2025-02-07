// 关于GAS系统的学习


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAureAttributeSet* AureAttributeSet = CastChecked<UAureAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AureAttributeSet->GetShengMingZhi());
	OnMaxHealthChanged.Broadcast(AureAttributeSet->GetMaxShengMingZhi());
	
	OnManaChanged.Broadcast(AureAttributeSet->GetMona());
	OnMaxManaChanged.Broadcast(AureAttributeSet->GetMaxMona());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAureAttributeSet* AureAttributeSet = CastChecked<UAureAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAttributeSet->GetShengMingZhiAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{

			OnHealthChanged.Broadcast(Data.NewValue);
		});


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAttributeSet->GetMaxShengMingZhiAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAttributeSet->GetMonaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnManaChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAttributeSet->GetMaxMonaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{

		OnMaxManaChanged.Broadcast(Data.NewValue);
	});



	Cast<UAureAbilitySystemComponentBase>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{

				//Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")));
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
	
}

// void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
// {
//
// 	OnHealthChanged.Broadcast(Data.NewValue);
// }

// void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxHealthChanged.Broadcast(Data.NewValue);
// }

// void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnManaChanged.Broadcast(Data.NewValue);
// }

// void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	
// 	OnMaxManaChanged.Broadcast(Data.NewValue);
// }
