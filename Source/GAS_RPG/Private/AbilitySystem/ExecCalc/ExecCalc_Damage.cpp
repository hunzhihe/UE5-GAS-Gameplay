// 关于GAS系统的学习


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AssetTypeCategories.h"
#include "AureGameplayTags.h"
#include "AureRPGAbilityTypes.h"
#include "../../../../../../../UE_5.5/Engine/Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagEditorUtilities.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "AbilitySystem/Date/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"



struct AureDamageStatics
{
	//目标
	DECLARE_ATTRIBUTE_CAPTUREDEF(HuJia)
	DECLARE_ATTRIBUTE_CAPTUREDEF(GeDang)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BaoJiResist)
	//--------抗性--------
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFire)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceIce)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceLightning)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistancePhysical)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceMagic)
	//源
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChuanJia)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BaoJiDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BaoJi)

	//存储标签和属性快照对应的map
TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagToCaptureDefs;
	
	AureDamageStatics()
	{
		//关于属性捕捉参数设置，  属性集  ，属性名  ， 目标还是自身，  是否设置快照（true为创建时获取，false为应用时获取）
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, HuJia, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, GeDang, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, BaoJiResist, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ChuanJia, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, BaoJiDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, BaoJi, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ResistanceFire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ResistanceIce, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ResistanceLightning, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ResistancePhysical, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAureAttributeSet, ResistanceMagic, Target, false);


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
	RelevantAttributesToCapture.Add(DamageStatics().GeDangDef);
	RelevantAttributesToCapture.Add(DamageStatics().ChuanJiaDef);
	RelevantAttributesToCapture.Add(DamageStatics().BaoJiDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().BaoJiResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().BaoJiDef);
	//---------抗性--------
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceFireDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceIceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceLightningDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistancePhysicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceMagicDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);



	//存储标签和属性快照对应的map
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagToCaptureDefs;

	const FAureGameplayTags& Tags = FAureGameplayTags::Get();

	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_HuJia,DamageStatics().HuJiaDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_GeDang,DamageStatics().GeDangDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_BaoJiResist,DamageStatics().BaoJiResistDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_ChuanJia,DamageStatics().ChuanJiaDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_BaoJiDamage,DamageStatics().BaoJiDamageDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Secondary_BaoJi,DamageStatics().BaoJiDef);

	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Damage_Resistance_Fire,DamageStatics().ResistanceFireDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Damage_Resistance_Ice,DamageStatics().ResistanceIceDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Damage_Resistance_Lightning,DamageStatics().ResistanceLightningDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Damage_Resistance_Physical,DamageStatics().ResistancePhysicalDef);
	TagToCaptureDefs.Add(FAureGameplayTags::Get().Attribute_Damage_Resistance_Magic,DamageStatics().ResistanceMagicDef);
    //获取ASC
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	//获取AvatarActor
	 AActor* SourceAvatarActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	 AActor* TargetAvatarActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;



	
	//获取战斗接口，以获取角色等级
    int32 SourcePlayerLevel = 1;
	if (SourceAvatarActor->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetLevel(SourceAvatarActor);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatarActor->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetLevel(TargetAvatarActor);
	}

	//获取挂载此类的GameplayEffect
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	//设置评估参数
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//获取角色配置信息
	const UCharacterClassInfo* CharacterClassInfo = UAureAbilitySysTEM_BFL::GetCharacterClassInfo(SourceAvatarActor);
    
	 FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
 //    FAureRPGGameplayEffectContext* Context = static_cast<FAureRPGGameplayEffectContext*>(EffectContext);

	//Debuff
	DetermineDebuff(ExecutionParams,Spec,EvaluationParameters,TagToCaptureDefs);

	//----------触发抗性----------
    //获取伤害值
	float Damage = 0;
	for (const TTuple<FGameplayTag,FGameplayTag>& Pair :FAureGameplayTags::Get().DamageTypesToResistance)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagToCaptureDefs.Contains(ResistanceTag), TEXT("TagToCaptureDefs does not contain ResistanceTag:[%s] inExecCalc_Damage"),*ResistanceTag.GetTagName().ToString());

		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagToCaptureDefs[ResistanceTag];


		float DamageTypeValue = 0;
		DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);

		

		float Resistance = 0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp<float>(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		
		Damage += DamageTypeValue; 
	}
	
	//Damage = Damage-10;
	

    //------------触发格挡期-----------
	//获取格挡属性
	float GeDang = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().GeDangDef, EvaluationParameters, GeDang);
	GeDang = FMath::Max<float>(GeDang, 0.f);
	//触发格挡，生成随机数机型格挡率判断，随机数小于格挡率，则触发格挡，伤害减半
	const bool bBlocked = FMath::RandRange(1, 100) < GeDang;
	UAureAbilitySysTEM_BFL::SetBlockedHit(EffectContextHandle, bBlocked);
	if (bBlocked)
	{
		Damage *=0.5f;
	}

	//----------触发护甲以及护甲穿透-------
	//获取护甲属性
	float HuJia = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HuJiaDef, EvaluationParameters, HuJia);
	HuJia = FMath::Max<float>(HuJia, 0.f);


	//获取穿甲属性
	float ChuanJia = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ChuanJiaDef, EvaluationParameters, ChuanJia);
	ChuanJia = FMath::Max<float>(ChuanJia, 0.f);
    //从数据表中获取穿甲系数
	FRealCurve* ChanJiaCoeffCurve = CharacterClassInfo->DamageCalculationCoefficent->FindCurve(FName("ChuanJia"),FString());
    float ChanJiaCoeff = ChanJiaCoeffCurve->Eval(SourcePlayerLevel);
	//计算护甲穿透后的护甲值
	const float EffectiveHuJia = HuJia * (100.f-ChuanJia*ChanJiaCoeff) / 100.f;

	//从数据表中获取护甲系数
	FRealCurve* HuJiaCoeffCurve = CharacterClassInfo->DamageCalculationCoefficent->FindCurve(FName("HuJia"),FString());
	float HuJiaCoeff = HuJiaCoeffCurve->Eval(SourcePlayerLevel);
	
	//穿甲值忽略护甲之后，护甲值将按照一定比例影响伤害
	Damage *=(100.f-EffectiveHuJia*HuJiaCoeff)/100.f;


	//----------触发暴击-----------
	//获取暴击率属性
	float SourceBaoJi = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaoJiDef, EvaluationParameters, SourceBaoJi);
	SourceBaoJi = FMath::Max<float>(SourceBaoJi, 0.f);
	//获取暴击伤害属性
	float SourceBaoJiDamage = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaoJiDamageDef, EvaluationParameters, SourceBaoJiDamage);
	SourceBaoJiDamage = FMath::Max<float>(SourceBaoJiDamage, 0.f);
	//获取暴击抵抗
	float TargetBaoJiResist = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaoJiResistDef, EvaluationParameters, TargetBaoJiResist);
	TargetBaoJiResist = FMath::Max<float>(TargetBaoJiResist, 0.f);
	//获取数据表中的暴击抵抗系数
	FRealCurve* BaoJiResistCoeffCurve = CharacterClassInfo->DamageCalculationCoefficent->FindCurve(FName("BaoJiResist"),FString());
	float BaoJiResistCoeff = BaoJiResistCoeffCurve->Eval(TargetPlayerLevel);

	//判断当前是否暴击
	const float EffectiveBaoJi =SourceBaoJi-TargetBaoJiResist*BaoJiResistCoeff;
	const bool bCriticalHit = EffectiveBaoJi>FMath::RandRange(1, 100);
	UAureAbilitySysTEM_BFL::SetCriticalHit(EffectContextHandle, bCriticalHit);
	if (bCriticalHit)
	{
		Damage = Damage*2+SourceBaoJiDamage;
	}

	//----------触发抗性----------

	
	//输出属性计算结果
	const FGameplayModifierEvaluatedData EvaluatedData(UAureAttributeSet::GetMetaIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

 void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
 	const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters& EvaluationParameters,
 	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs)
 {
 	const FAureGameplayTags &Tags = FAureGameplayTags::Get();
 	//遍历所有的负面效果伤害类型，根据伤害类型是否赋值判断应用的负面效果
 	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : Tags.DamageTypesToResistance)
 	{
 		FGameplayTag DamageTypeTag = Pair.Key;//获取到负面效果的伤害类型
 		const FGameplayTag ResistanceTag = Pair.Value;//获取到负面效果的抗性类型
 		const float TypeDamage = Spec.GetSetByCallerMagnitude(Tags.DeBuff_Damage, false, -1.f);

 		//如果负面效果设置了伤害，则应用负面效果
 		if (TypeDamage>-.5f)
 		{
 			//获取负面效果命中率
 			const float SoureDeBuffChance = Spec.GetSetByCallerMagnitude(Tags.DeBuff_Chance, false, -1.f);

 			//_____________获取负面效果抵抗----------
 			float TargetDeBuffResist = 0.f;//计算目标对收到负面效果的抵抗
 			checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("无法获取到Tag:[%s]对应的属性快照 inExecCalc_Damage"), *ResistanceTag.GetTagName().ToString());
 			//通过抗性标签获取到属性快照的值
 			const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];
 			
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, TargetDeBuffResist);
 			
			TargetDeBuffResist = FMath::Clamp<float>(TargetDeBuffResist, 0.f, 100.f);//限制 resist为0-100


 			//--------计算触发负面效果---------
 			const float EffectiveDeBuffChance = SoureDeBuffChance* (100.f - TargetDeBuffResist) / 100.f ;//计算触发负面效果的概率
 			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDeBuffChance;//随机数小于触发负面效果的概率，则触发负面效果
 			if (bDebuff)
 			{
 				//获取GE上下文设置负面效果相关配置
 				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();
 				//设置当前应用负面效果成功
				UAureAbilitySysTEM_BFL::SetDeBuffApplied(ContextHandle, true);

 				const float DeBuffDuration = Spec.GetSetByCallerMagnitude(Tags.DeBuff_Duration, false, 0.f);
 				const float DeBuffFrequency = Spec.GetSetByCallerMagnitude(Tags.DeBuff_Frequency, false, 0.f);

 				//设置负面效果相关配置
 				UAureAbilitySysTEM_BFL::SetDeBuff(ContextHandle, DamageTypeTag, TypeDamage, DeBuffDuration, DeBuffFrequency);
 				
 			}
 		}
 	}
 }
