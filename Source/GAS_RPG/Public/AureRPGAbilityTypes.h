#pragma once

#include"GameplayEffectTypes.h"
#include"AureRPGAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams()
	{}

	//当前场景上下文对象
	UPROPERTY()
	TObjectPtr<UObject> WorkContextObject = nullptr;
	//需要应用的GE的类
	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;
	//源ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;
	//目标ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	//技能基础伤害
	UPROPERTY()
	float BaseDamage = 0.f;
	//技能等级
	UPROPERTY()
	int32 AbilityLevel = 1;

	//负面效果伤害类型
	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();

	// 负面效果的伤害发生概率
	UPROPERTY()
	float DeBuffChance = 0.f;
	// 负面效果的伤害
	UPROPERTY()
	float DeBuffDamage = 0.f;
	// 负面效果的持续时间
	UPROPERTY()
	float DeBuffDuration = 0.f;
	//负面效果的频率
	UPROPERTY()
	float DeBuffFrequency = 0.f;

	//角色死亡时受到的冲击力
	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;
	//死亡时冲击力朝向
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	//角色被攻击时受到的冲击力概率
	UPROPERTY()
	float KnockbackChance = 0.f;

	//攻击时击退的力度
	UPROPERTY()
	float KnockbackForceMagnitude = 0.f;
	//攻击时击退的方向
	UPROPERTY()
	FVector KnockbackForceDirection = FVector::ZeroVector;

};




USTRUCT(BlueprintType)
struct FAureRPGGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	//添加获取函数和设置函数
	 bool IsBlockedHit() const { return bIsBlockedHit; }
	 bool IsCriticalHit() const { return bIsCriticalHit; }
	 bool IsDeBuffApplied() const { return bIsDeBuffApplied; }
	 float GetDeBuffDamage() const { return DeBuffDamage; }
	 float GetDeBuffDuration() const { return DeBuffDuration; }
	 float GetDeBuffFrequency() const { return DeBuffFrequency; }
	 TSharedPtr<FGameplayTag> GetDeBuffDamageType() const { return DamageType; }
	//
	 void SetBlockedHit(const bool bInBlockedHit) { bIsBlockedHit = bInBlockedHit;}
	 void SetCriticalHit(const bool bInCriticalHit) { bIsCriticalHit = bInCriticalHit;}
	 void SetDeBuffApplied(const bool bInDeBuffApplied) { bIsDeBuffApplied = bInDeBuffApplied;}
	 void SetDeBuffDamage(const float InDeBuffDamage) { DeBuffDamage = InDeBuffDamage;}
	 void SetDeBuffDuration(const float InDeBuffDuration) { DeBuffDuration = InDeBuffDuration;}
	 void SetDeBuffFrequency(const float InDeBuffFrequency) { DeBuffFrequency = InDeBuffFrequency;}
	 void SetDeBuffDamageType(const TSharedPtr<FGameplayTag>& InDamageType) { DamageType = InDamageType;}

	
    // 重写GetScriptStruct函数，返回用于序列化的FGameplayEffectContext的静态结构体
	virtual UScriptStruct* GetScriptStruct() const override { return FGameplayEffectContext::StaticStruct(); }
	/* 重写NetSerialize函数，用于网络序列化,
	 FArchive& Ar 是Unreal Engine中用于序列化和反序列化对象的类，它支持以二进制的形式进行加载保存和垃圾回收。
	class UPackageMap* Map 用于查找或记录对象间的引用关系
	bool& bOutSuccess 输出是否序列化成功
	*/
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	// 重写Duplicate函数，复制对象,用于后续网络复制或者后续修改
	virtual FAureRPGGameplayEffectContext* Duplicate() const override
	{
		FAureRPGGameplayEffectContext* NewContext = new FAureRPGGameplayEffectContext();
		*NewContext = *this;//With Copy为true，会自动调用复制构造函数
		if (GetHitResult())
		{
			//深拷贝
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	};


	//获取到死亡冲击的方向和力度
	FVector GetDeathImpulse() const{return  DeathImpulse;}
	//设置死亡冲击方向和力度
	void SetDeathImpulse(const FVector& InDeathImpulse) { DeathImpulse = InDeathImpulse;}
	//获取到攻击时击退的方向和力度
	FVector GetKnockbackForceDirection() const { return KnockbackForceDirection; }
	//设置攻击时击退的方向和力度
	void SetKnockbackForceDirection(const FVector& InKnockbackForceDirection) { KnockbackForceDirection = InKnockbackForceDirection;}


protected:
	UPROPERTY()//格挡
	bool bIsBlockedHit = false;
	UPROPERTY()//是否是暴击
	bool bIsCriticalHit = false;

	//成功应用负面效果
	UPROPERTY()
	bool bIsDeBuffApplied = false;
	//负面效果每次造成伤害
	UPROPERTY()
	float DeBuffDamage = 0.f;
	//负面效果持续时间
	UPROPERTY()
	float DeBuffDuration = 0.f;
	//负面效果频率
	UPROPERTY()
	float DeBuffFrequency = 0.f;

	//负面效果的伤害类型
	TSharedPtr<FGameplayTag> DamageType;

	//死亡时受到冲击力朝向
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	//攻击时击退的方向
	UPROPERTY()
	FVector KnockbackForceDirection = FVector::ZeroVector;
};

template <>
struct TStructOpsTypeTraits<FAureRPGGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAureRPGGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
