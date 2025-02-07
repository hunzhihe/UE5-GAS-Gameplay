// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Date/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AureAbilitySysTEM_BFL.generated.h"

class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureAbilitySysTEM_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController")
	static  UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController")
	static  UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject,UAbilitySystemComponent* AbilitySystemComponent);
};
