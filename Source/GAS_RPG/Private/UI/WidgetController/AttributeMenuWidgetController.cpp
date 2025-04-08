// 关于GAS系统的学习


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "AbilitySystem/Date/AttributeInfo_DataAsset.h"
#include "Player/APlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    const AAPlayerState* PS = CastChecked<AAPlayerState>(PlayerState);
    AttributePointsChangedDelegate.Broadcast(PS->GetAttributePoints());
	
	UAureAttributeSet* AS = Cast<UAureAttributeSet>(AttributeSet);
	check(AttributeInfo)
	for (auto& TagToAttribute :AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(TagToAttribute.Key,TagToAttribute.Value());

	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

	//UAureAttributeSet* AS = Cast<UAureAttributeSet>(AttributeSet);
	check(AttributeInfo)
	for (auto& TagToAttribute :GetAureAttributeSet()->TagsToAttributes)
	{
       AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagToAttribute.Value()).AddLambda(
       [this,TagToAttribute](const FOnAttributeChangeData& Data)
       {
	     BroadcastAttributeInfo(TagToAttribute.Key,TagToAttribute.Value()); 		
       }
       );
	}
	//AAPlayerState* PS = Cast<AAPlayerState>(PlayerState);
	//绑定PlayState的属性点委托
	GetAurePlayerState()->OnAttributePointsChangedDelegate.AddLambda([this](int32 Points)
	{

	  AttributePointsChangedDelegate.Broadcast(Points);
		
	});
	
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	//UAureAbilitySystemComponentBase* ASC = CastChecked<UAureAbilitySystemComponentBase>(AbilitySystemComponent);
	GetAureAbilitySystemComponent()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAureAttributeInfo Tag = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	//FGameplayAttribute Attribute = TagToAttribute.Value.Execute();
	Tag.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	AttributeInfoDelegate.Broadcast(Tag);
}
