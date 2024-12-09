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


UCLASS()
class GAS_RPG_API UAureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAureAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override; 

	//生命值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ShengMingZhi,Category="Attribute")
	FGameplayAttributeData ShengMingZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,ShengMingZhi);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxShengMingZhi,Category="Attribute")
	FGameplayAttributeData MaxShengMingZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MaxShengMingZhi);
	
	//体力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_TiLiZhi,Category="Attribute")
	FGameplayAttributeData TiLiZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,TiLiZhi);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxTiLiZhi,Category="Attribute")
	FGameplayAttributeData MaxTiLiZhi;
	ATTRIBUTE_ACCESSORS(UAureAttributeSet,MaxTiLiZhi);

    UFUNCTION()
	void OnRep_ShengMingZhi(const FGameplayAttributeData& OldShengMingZhi) const;
	UFUNCTION()
	void OnRep_MaxShengMingZhi(const FGameplayAttributeData& OldMaxShengMingZhi) const;

	UFUNCTION()
	void OnRep_TiLiZhi(const FGameplayAttributeData& OldTiLiZhi) const;
	UFUNCTION()
	void OnRep_MaxTiLiZhi(const FGameplayAttributeData& OldMaxTiLiZhi)const;
	
};
