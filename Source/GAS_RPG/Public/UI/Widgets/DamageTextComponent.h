// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,Category = "DamageText")
	void SetDamageText(float Damage, bool bBlockedHit, bool bCriticalHit);
};
