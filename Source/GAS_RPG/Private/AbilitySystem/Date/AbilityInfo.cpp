// 关于GAS系统的学习


#include "AbilitySystem/Date/AbilityInfo.h"
#include "GAS_RPG/AureLogChannels.h"

FAureAbilityInfo UAbilityInfo::GetAbilityInfoByTag(const FGameplayTag& AbilityTag, bool blogNotFound) const
{
	for (const FAureAbilityInfo& Info : AbilityInfo)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if (blogNotFound)
	{
		//如果获取不到技能数据，则输出日志信息
		UE_LOG(LogAure, Warning, TEXT("无法通过技能标签[%s]在技能数据[%s]查找到对应的技能数据"), *AbilityTag.ToString(),*GetNameSafe(this));
	}
	return FAureAbilityInfo();
}
