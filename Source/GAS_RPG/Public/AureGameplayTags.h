// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * 
 */
struct FAureGameplayTags
{
public:

    static const FAureGameplayTags& Get()
    {
        return GameplayTags;
    }

	static void InitializeNativeGameplayTags();

	//主要属性
	FGameplayTag Attribute_Primary_LiLiang;
	FGameplayTag Attribute_Primary_NaiLi;
	FGameplayTag Attribute_Primary_MinJie;
	FGameplayTag Attribute_Primary_ZhiLi;


	
	/*次要属性*/
	FGameplayTag Attribute_Secondary_HuJia;
    FGameplayTag Attribute_Secondary_BaoJi;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
    FGameplayTag Attribute_Secondary_ChuanJia;
    FGameplayTag Attribute_Secondary_GeDang;
    FGameplayTag Attribute_Secondary_BaoJiDamage;
    FGameplayTag Attribute_Secondary_BaoJiResist;
    FGameplayTag Attribute_Secondary_ShengMingRegener;
    FGameplayTag Attribute_Secondary_MonaRegener;
	//重要属性
    FGameplayTag Attribute_Vital_ShengMingZhi;
	FGameplayTag Attribute_Vital_Mona;


	//输入
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	//伤害类型
	FGameplayTag Attribute_Damage;
	FGameplayTag Attribute_Damage_Fire;
	FGameplayTag Attribute_Damage_Ice;
	FGameplayTag Attribute_Damage_Lightning;
	FGameplayTag Attribute_Damage_Physical;
	FGameplayTag Attribute_Damage_True;
	FGameplayTag Attribute_Damage_Magic;
	FGameplayTag Attribute_Damage_Critical;
	FGameplayTag Attribute_Damage_Penetration;


	//受击标签
	FGameplayTag Effects_HitReact;

protected:

private:
 
	static FAureGameplayTags GameplayTags;
 
};