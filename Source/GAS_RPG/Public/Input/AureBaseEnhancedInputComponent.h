// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "DA_Input.h"
#include "EnhancedInputComponent.h"
#include "AureBaseEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureBaseEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType,typename HoldFuncType>
	void BindAbilityAction( const UAureDA_Input* DA_Input, UserClass* Object,PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HoldFuncType HoldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HoldFuncType>
void UAureBaseEnhancedInputComponent::BindAbilityAction(const UAureDA_Input* DA_Input, UserClass* Object,PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, HoldFuncType HoldFunc)
{
	check(DA_Input)
	for (const FAureInputAction& Action : DA_Input->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTags.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc,Action.InputTags);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc,Action.InputTags);
			}
			if (HoldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HoldFunc,Action.InputTags);
			}
		}
	}
}
