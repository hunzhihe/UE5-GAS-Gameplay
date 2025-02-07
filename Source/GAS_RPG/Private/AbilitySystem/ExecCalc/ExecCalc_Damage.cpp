// 关于GAS系统的学习


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystem/AureAttributeSet.h"

struct AureDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HuJia)
	AureDamageStatics()
	{
		//关于属性捕捉参数设置，  属性集  ，属性名  ， 目标还是自身，  是否设置快照（true为创建时获取，false为应用时获取）
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, HuJia, Target, false);
		
	}
};
static const AureDamageStatics& DamageStatics()
{
	 static AureDamageStatics DStatics;
	 return DStatics;
};

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().HuJiaDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
    //获取ASC
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	//获取AvatarActor
	const AActor* SourceAvatarActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatarActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	//获取挂载此类的GameplayEffect
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	//设置评估参数
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;



	//获取护甲属性
	float HuJia = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HuJiaDef, EvaluationParameters, HuJia);
	HuJia = FMath::Max<float>(HuJia, 0.f);
    ++HuJia;
	//输出属性计算结果
	const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().HuJiaProperty, EGameplayModOp::Additive, HuJia);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
