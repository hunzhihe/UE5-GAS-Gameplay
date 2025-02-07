// 关于GAS系统的学习


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AureAttributeSet.h"
#include "AbilitySystem/Date/AttributeInfo_DataAsset.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAureAttributeSet* AS = Cast<UAureAttributeSet>(AttributeSet);
	check(AttributeInfo)

	// FAureAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAureGameplayTags::Get().Attribute_Primary_LiLiang);
	// Info.AttributeValue = AS->LiLiang.GetCurrentValue();
	// AttributeInfoDelegate.Broadcast(Info);


	for (auto& TagToAttribute :AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(TagToAttribute.Key,TagToAttribute.Value());

	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAureAttributeSet* AS = Cast<UAureAttributeSet>(AttributeSet);
	check(AttributeInfo)

	// FAureAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAureGameplayTags::Get().Attribute_Primary_LiLiang);
	// Info.AttributeValue = AS->LiLiang.GetCurrentValue();
	// AttributeInfoDelegate.Broadcast(Info);


	for (auto& TagToAttribute :AS->TagsToAttributes)
	{
       AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagToAttribute.Value()).AddLambda(
       [this,TagToAttribute](const FOnAttributeChangeData& Data)
       {
	     BroadcastAttributeInfo(TagToAttribute.Key,TagToAttribute.Value()); 		
       }
       );

	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAureAttributeInfo Tag = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	//FGameplayAttribute Attribute = TagToAttribute.Value.Execute();
	Tag.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	AttributeInfoDelegate.Broadcast(Tag);

	
}
