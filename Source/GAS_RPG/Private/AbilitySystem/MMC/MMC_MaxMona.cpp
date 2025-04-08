// 关于GAS系统的学习


#include "AbilitySystem/MMC/MMC_MaxMona.h"

#include "AbilitySystem/AureAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMona::UMMC_MaxMona()
{
	ZhiLiDef.AttributeToCapture = UAureAttributeSet::GetZhiLiAttribute();
	ZhiLiDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ZhiLiDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ZhiLiDef);
}

float UMMC_MaxMona::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer * SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer * TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float ZhiLi = 0.f;
	GetCapturedAttributeMagnitude(ZhiLiDef, Spec, EvaluationParameters, ZhiLi);
	ZhiLi = FMath::Max<float>(ZhiLi, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetLevel(Spec.GetContext().GetSourceObject());
	}
	return 50.f + 2.5 * PlayerLevel + 5.0f * ZhiLi;
}
