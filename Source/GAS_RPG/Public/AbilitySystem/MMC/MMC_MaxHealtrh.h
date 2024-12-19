// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealtrh.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UMMC_MaxHealtrh : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxHealtrh();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	FGameplayEffectAttributeCaptureDefinition NaiLiDef;
};
