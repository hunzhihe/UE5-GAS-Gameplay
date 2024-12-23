// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AureWidgetController.h"
#include "AureUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(); 
	
};
