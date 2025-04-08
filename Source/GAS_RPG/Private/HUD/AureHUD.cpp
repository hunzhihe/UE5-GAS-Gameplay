// 关于GAS系统的学习


#include "HUD/AureHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"

UOverlayWidgetController* AAureHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallbacksToDependencies();

		return  OverlayWidgetController;
	}
	
return OverlayWidgetController;
	
}


void AAureHUD::InitOverlayWidget(APlayerController* PlayerController, APlayerState* PlayerState,
                                 UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
    checkf(OverlayWidgetClass,TEXT("Overlay Widget class is null,请检查"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class is null,请检查"));
	UUserWidget* Widget =   CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);

	OverlayWidget = Cast<UAureUserWidget>(Widget);

	const  FWidgetControllerParams WidgetControllerParams(PlayerController,AttributeSet,PlayerState,AbilitySystemComponent);
    UOverlayWidgetController* WidgetController =GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(OverlayWidgetController);

	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

UAttributeMenuWidgetController* AAureHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{

		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();

		return  AttributeMenuWidgetController;
	}
	return AttributeMenuWidgetController;
}

USpellMenuWidgetController* AAureHUD::GetSpellMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (SpellMenuWidgetController == nullptr)
	{
		SpellMenuWidgetController = NewObject<USpellMenuWidgetController>( this,SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(WCParams);
		SpellMenuWidgetController->BindCallbacksToDependencies();
	}

	return SpellMenuWidgetController;
}


