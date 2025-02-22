// 关于GAS系统的学习


#include "UI/WidgetController/AureWidgetController.h"

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
