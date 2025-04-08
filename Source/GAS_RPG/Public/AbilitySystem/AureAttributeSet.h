// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AureAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//DECLARE_DELEGATE_RetVal(FGameplayAttribute,FAttributeSiginature);
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
    UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
    UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};
//或者在Tmap处直接使用函数指针
typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;

UCLASS()
class GAS_RPG_API UAureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAureAttributeSet();

	//发送经验事件
	static void SendXPEvent(const FEffectProperties& Properties);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	static void ShowFloatText(const FEffectProperties& Properties, float LocalIncomingDamage, bool IsBlockedHit, bool bIsCriticalHit);

	
	/**
* 在执行 GameplayEffect 后立即调用，以修改属性的基值。无法再进行更多更改。
* 请注意，这仅在 'execute' 期间调用。例如，对属性的 'base value' 的修改。在应用 GameplayEffect 期间（例如 5 秒 +10 移动速度增益），不会调用它。
*/
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//在属性变更时可触发
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	//也可以换成函数指针  TMap<FGameplayTag,  FGameplayAttribute(*)()>TagsToAttributes;
	TMap<FGameplayTag, FAttributeFuncPtr>TagsToAttributes;
	
	//生命值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ShengMingZhi,Category="Attribute")
	FGameplayAttributeData ShengMingZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ShengMingZhi);
	
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxShengMingZhi,Category="Primary Attribute")
	FGameplayAttributeData MaxShengMingZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MaxShengMingZhi);
	
	//魔法值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mona,Category="Attribute")
	FGameplayAttributeData Mona;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,Mona);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMona,Category="Primary Attribute")
	FGameplayAttributeData MaxMona;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MaxMona);

	//主属性
	//力量
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_LiLiang,Category="Primary Attribute")
	FGameplayAttributeData LiLiang;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,LiLiang);

    //主属性智力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ZhiLi,Category="Primary Attribute")
	FGameplayAttributeData ZhiLi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ZhiLi);

	//主属性敏捷
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MinJie,Category="Primary Attribute")
	FGameplayAttributeData MinJie;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MinJie);

	//主属性耐力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_NaiLi,Category="Primary Attribute")
	FGameplayAttributeData NaiLi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,NaiLi);

	//次要属性 护甲，依附于主属性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HuJia,Category="Secondary Attribute")
	FGameplayAttributeData HuJia;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,HuJia);

	//次要属性 穿甲，依附于主属性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ChuanJia,Category="Secondary Attribute")
	FGameplayAttributeData ChuanJia;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ChuanJia);

	//次要属性 格挡

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_GeDang,Category="Secondary Attribute")
	FGameplayAttributeData GeDang;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,GeDang);

	//次要属性 暴击
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BaoJi,Category="Secondary Attribute")
	FGameplayAttributeData BaoJi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,BaoJi);

	//次要属性 暴击伤害
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BaoJiDamage,Category="Secondary Attribute")
	FGameplayAttributeData BaoJiDamage;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,BaoJiDamage);
	
	//次要属性 暴击抵抗
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BaoJiResist,Category="Secondary Attribute")
	FGameplayAttributeData BaoJiResist;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,BaoJiResist);

	//次要属性 生命恢复
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ShengMingRegener,Category="Secondary Attribute")
	FGameplayAttributeData ShengMingRegener;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ShengMingRegener);

	//次要属性 魔法恢复
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MonaRegener,Category="Secondary Attribute")
	FGameplayAttributeData MonaRegener;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MonaRegener);

	//----------抗性----------
	//次要属性 火焰抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ResistanceFire,Category="Secondary Attribute")
	FGameplayAttributeData ResistanceFire;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ResistanceFire);

	//次要属性 冰冻抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ResistanceIce,Category="Secondary Attribute")
	FGameplayAttributeData ResistanceIce;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ResistanceIce);

	//次要属性 电击抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ResistanceLightning,Category="Secondary Attribute")
	FGameplayAttributeData ResistanceLightning;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ResistanceLightning);

	//次要属性 魔法抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ResistanceMagic,Category="Secondary Attribute")
	FGameplayAttributeData ResistanceMagic;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ResistanceMagic);

	//次要属性 物理抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ResistancePhysical,Category="Secondary Attribute")
	FGameplayAttributeData ResistancePhysical;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ResistancePhysical);


	/*
	 *伤害元属性
	 */
    UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData MetaIncomingDamage;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MetaIncomingDamage);

	//经验元属性
	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,IncomingXP);
	

	
    
    UFUNCTION()
	void OnRep_ShengMingZhi(const FGameplayAttributeData& OldShengMingZhi) const;
	UFUNCTION()
	void OnRep_MaxShengMingZhi(const FGameplayAttributeData& OldMaxShengMingZhi) const;

	UFUNCTION()
	void OnRep_Mona(const FGameplayAttributeData& OldMona) const;
	UFUNCTION()
	void OnRep_MaxMona(const FGameplayAttributeData& OldMaxMona)const;
/*
 * 主属性回复
 */
	UFUNCTION()
	void OnRep_LiLiang(const FGameplayAttributeData& OldLiLiang) const;
	UFUNCTION()
	void OnRep_ZhiLi(const FGameplayAttributeData& OldZhiLi) const;
	UFUNCTION()
	void OnRep_MinJie(const FGameplayAttributeData& OldMinJie )const;
	UFUNCTION()
	void OnRep_NaiLi(const FGameplayAttributeData& OldNaiLi )const;
    
/*
 * 次属性回复
 */
	UFUNCTION()
	void OnRep_HuJia(const FGameplayAttributeData& OldHuJia) const;
	UFUNCTION()
	void OnRep_ChuanJia(const FGameplayAttributeData& OldChuanJia) const;
	UFUNCTION()
	void OnRep_GeDang(const FGameplayAttributeData& OldGeDang) const;
	UFUNCTION()
	void OnRep_BaoJi(const FGameplayAttributeData& OldBaoJi) const;
	UFUNCTION()
	void OnRep_BaoJiDamage(const FGameplayAttributeData& OldBaoJiDamage) const;
	UFUNCTION()
	void OnRep_BaoJiResist(const FGameplayAttributeData& OldBaoJiResist) const;
	UFUNCTION()
	void OnRep_ShengMingRegener(const FGameplayAttributeData& OldShengMingRegener) const;
	UFUNCTION()
	void OnRep_MonaRegener(const FGameplayAttributeData& OldMonaRegener) const;
	UFUNCTION()
	void OnRep_ResistanceFire(const FGameplayAttributeData& OldResistanceFire) const;
	UFUNCTION()
	void OnRep_ResistanceIce(const FGameplayAttributeData& OldResistanceIce) const;
	UFUNCTION()
	void OnRep_ResistanceLightning(const FGameplayAttributeData& OldResistanceLightning) const;
	UFUNCTION()
	void OnRep_ResistanceMagic(const FGameplayAttributeData& OldResistanceMagic) const;
	UFUNCTION()
	void OnRep_ResistancePhysical(const FGameplayAttributeData& OldResistancePhysical) const;

	//处理传入的参数为伤害属性时，处理的逻辑
	void HandleIncomeingDamage(const FEffectProperties& Properties);

	//处理传入的参数是经验属性时，处理的逻辑
	void HandleIncomingXP(const FEffectProperties& Properties);

	//如果当前伤害出发了负面效果，处理逻辑
	void HandleDeBuff(const FEffectProperties& Properties);
	
private:
	static void SetEffectProperties( const FGameplayEffectModCallbackData& Data , FEffectProperties& EffectProperties );
};
