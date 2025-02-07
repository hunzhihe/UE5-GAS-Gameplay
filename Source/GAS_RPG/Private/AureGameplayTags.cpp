// 关于GAS系统的学习


#include "AureGameplayTags.h"

#include "GameplayTagsManager.h"

FAureGameplayTags FAureGameplayTags::GameplayTags;

void FAureGameplayTags::InitializeNativeGameplayTags()
{
   //主属性标签初始化
   GameplayTags.Attribute_Primary_LiLiang= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.LiLiang"),FString ("力量,增加攻击力"));
   GameplayTags.Attribute_Primary_MinJie= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.MinJie"),FString ("敏捷,增加防御，暴击"));
   GameplayTags.Attribute_Primary_NaiLi= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.NaiLi"),FString ("耐力,增加生命值，增加回复"));
   GameplayTags.Attribute_Primary_ZhiLi= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.ZhiLi"),FString ("智力,增加法术伤害，增加回复"));



   //副属性标签初始化
   GameplayTags.Attribute_Secondary_HuJia= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HuJia"),FString ("护甲,减少伤害，提升格挡"));
   GameplayTags.Attribute_Secondary_BaoJi= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BaoJi"),FString ("暴击,增加伤害"));
   GameplayTags.Attribute_Secondary_MaxHealth= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString ("最大生命值"));
   GameplayTags.Attribute_Secondary_MaxMana= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString ("最大法力值"));
   GameplayTags.Attribute_Secondary_ChuanJia= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ChuanJia"),FString ("穿甲,伤害"));
   GameplayTags.Attribute_Secondary_GeDang= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.GeDang"),FString ("格挡,减少伤害"));
   GameplayTags.Attribute_Secondary_BaoJiDamage= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BaoJiDamage"),FString ("暴击伤害"));
   GameplayTags.Attribute_Secondary_BaoJiResist= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BaoJiResist"),FString ("暴击抵抗"));
   GameplayTags.Attribute_Secondary_ShengMingRegener= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ShengMingRegener"),FString ("生命回复"));
   GameplayTags.Attribute_Secondary_MonaRegener= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MonaRegener"),FString ("法力回复"));
   
   //重要属性
   GameplayTags.Attribute_Vital_ShengMingZhi= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.ShengMingZhi"),FString ("生命值"));
   GameplayTags.Attribute_Vital_Mona= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Mona"),FString ("法力值"));

   //输入
   GameplayTags.InputTag_1= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString ("自定义1"));
   GameplayTags.InputTag_2= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString ("自定义2"));
   GameplayTags.InputTag_3= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString ("自定义3"));
   GameplayTags.InputTag_4= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString ("自定义4"));
   GameplayTags.InputTag_LMB= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString ("左键"));
   GameplayTags.InputTag_RMB= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString ("右键"));

   //伤害
   GameplayTags.Attribute_Damage= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage"),FString ("伤害"));
   GameplayTags.Attribute_Damage_Critical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Critical"),FString ("暴击伤害"));
   GameplayTags.Attribute_Damage_Fire= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Fire"),FString ("火焰伤害"));
   GameplayTags.Attribute_Damage_Ice= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Ice"),FString ("冰冻伤害"));
   //GameplayTags.Attribute_Damage_Electric= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Electric"),FString ("电击伤害"));
   GameplayTags.Attribute_Damage_Physical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Physical"),FString ("物理伤害"));
   GameplayTags.Attribute_Damage_Magic= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Magical"),FString ("魔法伤害"));
   GameplayTags.Attribute_Damage_Lightning= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Lightning"),FString ("雷电伤害"));
   GameplayTags.Attribute_Damage_Penetration= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Penetration"),FString ("穿透伤害"));
   GameplayTags.Attribute_Damage_True= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.True"),FString ("真实伤害"));
   
   //受击
   GameplayTags.Effects_HitReact= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects_HitReact"),FString ("受到攻击时，赋予的标签"));




   
}
