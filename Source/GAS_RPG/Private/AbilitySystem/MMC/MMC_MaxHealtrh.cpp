// 关于GAS系统的学习


#include "AbilitySystem/MMC/MMC_MaxHealtrh.h"

#include "AbilitySystem/AureAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealtrh::UMMC_MaxHealtrh()
{
    NaiLiDef.AttributeToCapture = UAureAttributeSet::GetNaiLiAttribute();
	NaiLiDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	NaiLiDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(NaiLiDef);
	
}

float UMMC_MaxHealtrh::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
    
    FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float NaiLi = 0.f;
    GetCapturedAttributeMagnitude(NaiLiDef, Spec, EvaluationParameters,NaiLi);
    NaiLi = FMath::Max<float>(NaiLi, 0.f);
	ICombatInterface* Interface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    const int32 PlayerLevel = Interface->GetLevel();

	return 80.f+ 2.5f *NaiLi + 10.f;
}
