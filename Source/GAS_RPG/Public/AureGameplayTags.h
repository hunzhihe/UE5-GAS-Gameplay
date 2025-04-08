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
    //被动技能输入标签
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	//伤害类型
	FGameplayTag Attribute_Damage;
	FGameplayTag Attribute_Damage_Fire;//火伤
	FGameplayTag Attribute_Damage_Ice;//`冰伤
	FGameplayTag Attribute_Damage_Lightning;//雷伤
	FGameplayTag Attribute_Damage_Physical;//物理伤害
	FGameplayTag Attribute_Damage_True;//真实伤害
	FGameplayTag Attribute_Damage_Magic;//法术伤害


	//受击标签
	FGameplayTag Effects_HitReact;

	//属性伤害抗性
	FGameplayTag Attribute_Damage_Resistance_Fire;
	FGameplayTag Attribute_Damage_Resistance_Ice;
	FGameplayTag Attribute_Damage_Resistance_Lightning;
	FGameplayTag Attribute_Damage_Resistance_Physical;
	//FGameplayTag Attribute_Damage_Resistance_True;
	FGameplayTag Attribute_Damage_Resistance_Magic;

    //技能标签
    FGameplayTag Abilities_None;
	
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Fire_Firebolt;//火球术技能
	FGameplayTag Abilities_Lightning_Electrocute;//雷电技能标签
	
	FGameplayTag Abilities_HitReact;

	FGameplayTag Abilities_Status_Locked;//技能状态标签 锁定
	FGameplayTag Abilities_Status_Eligible;//技能状态标签 可用
	FGameplayTag Abilities_Status_Unlocked;//技能状态标签 已解锁
	FGameplayTag Abilities_Status_Equipped;//技能状态标签 已装配

	FGameplayTag Abilities_Type_Offensive;//技能类型 主动
	FGameplayTag Abilities_Type_Passive;//技能类型 被动
	FGameplayTag Abilities_Type_None;//技能类型 空 

	//DeBuff标签
	FGameplayTag DeBuff_Burn;//火属性负面效果，燃烧
	FGameplayTag DeBuff_Stun;//雷属性负面效果 眩晕
	FGameplayTag DeBuff_Arcane;//魔法伤害负面效果
	FGameplayTag DeBuff_Physical;//物理伤害负面效果 流血

	//DeBuff配置标签
	FGameplayTag DeBuff_Duration;//持续时间
	FGameplayTag DeBuff_Frequency;//触发间隔
	FGameplayTag DeBuff_Damage;//伤害
	FGameplayTag DeBuff_Chance;//触发几率




	
	//技能冷却标签
	FGameplayTag Cooldown_Fire_FireBolt;
	FGameplayTag Cooldown_Lightning_Electrocute;


	
	//战斗插槽武器标签
	FGameplayTag CombatSocket_Weapon;
	//FGameplayTag Montage_Attack_Melee;在引擎默认标签中已经存在了
	FGameplayTag CombatSocket_RightHand;//右手攻击
	FGameplayTag CombatSocket_LeftHand;//左手攻击
	FGameplayTag CombatSocket_BothHands;//双手攻击
	FGameplayTag CombatSocket_Ranged;//远程攻击
	FGameplayTag CombatSocket_Tail;//尾部攻击

	//动画蒙太奇标签
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	//元属性
	FGameplayTag Attribute_Meta_IncomingXP;

	//属性和抗性标签
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistance;
    //属性伤害和相应负面Debuff标签
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;
	

private:
 
	static FAureGameplayTags GameplayTags;
 
}; 