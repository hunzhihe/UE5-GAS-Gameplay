// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 *
 * 
 */


UCLASS()
class GAS_RPG_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_Damage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	static void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluationParameters,
		TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs);
};
