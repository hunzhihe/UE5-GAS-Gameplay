// 关于GAS系统的学习


#include "Input/DA_Input.h"

const UInputAction* UAureDA_Input::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{

	for (const FAureInputAction& Action : AbilityInputActions)
	{
		if (Action.InputTags.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("未找到符合的驶入标签"))
	}
	return nullptr;
}
