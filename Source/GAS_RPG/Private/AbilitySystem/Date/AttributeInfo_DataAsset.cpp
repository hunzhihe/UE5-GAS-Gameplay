// 关于GAS系统的学习


#include "AbilitySystem/Date/AttributeInfo_DataAsset.h"

FAureAttributeInfo UAttributeInfo_DataAsset::FindAttributeInfoForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{

	for (const FAureAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(Tag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AttributeInfo for tag [%s] on AttributeInfo [%s]."),*Tag.ToString(),*GetNameSafe(this));
	}

	return FAureAttributeInfo();
}
