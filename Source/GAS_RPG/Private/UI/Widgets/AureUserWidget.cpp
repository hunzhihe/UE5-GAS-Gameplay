// 关于GAS系统的学习


#include "UI/Widgets/AureUserWidget.h"

void UAureUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
