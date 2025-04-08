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
   //被动技能输入标签
   GameplayTags.InputTag_Passive_1= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"),FString ("被动1"));
   GameplayTags.InputTag_Passive_2= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"),FString ("被动2"));
   //伤害
   GameplayTags.Attribute_Damage= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage"),FString ("伤害"));
   //GameplayTags.Attribute_Damage_Critical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Critical"),FString ("暴击伤害"));
   GameplayTags.Attribute_Damage_Fire= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Fire"),FString ("火焰伤害"));
   GameplayTags.Attribute_Damage_Ice= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Ice"),FString ("冰冻伤害"));
   //GameplayTags.Attribute_Damage_Electric= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Electric"),FString ("电击伤害"));
   GameplayTags.Attribute_Damage_Physical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Physical"),FString ("物理伤害"));
   GameplayTags.Attribute_Damage_Magic= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Magical"),FString ("魔法伤害"));
   GameplayTags.Attribute_Damage_Lightning= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Lightning"),FString ("雷电伤害"));
   //GameplayTags.Attribute_Damage_Penetration= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Penetration"),FString ("穿透伤害"));
   GameplayTags.Attribute_Damage_True= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.True"),FString ("真实伤害"));
   


   //抗性属性
   GameplayTags.Attribute_Damage_Resistance_Physical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.Physical"),FString ("物理伤害抗性"));
   GameplayTags.Attribute_Damage_Resistance_Fire= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.Fire"),FString ("火焰伤害抗性"));
   GameplayTags.Attribute_Damage_Resistance_Ice= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.Ice"),FString ("冰冻伤害抗性"));
   GameplayTags.Attribute_Damage_Resistance_Lightning= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.Lightning"),FString ("雷电伤害抗性"));
   GameplayTags.Attribute_Damage_Resistance_Magic= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.Magical"),FString ("魔法伤害抗性"));
   //GameplayTags.Attribute_Damage_Resistance_True= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Damage.Resistance.True"),FString ("真实伤害抗性"));

   //受击，空 类型技能标签
   GameplayTags.Effects_HitReact= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects_HitReact"),FString ("受到攻击时，赋予的标签"));
   GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"),FString ("无"));
   //Abilities 技能标签
   GameplayTags.Abilities_Attack= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"),FString ("攻击技能标签"));
   GameplayTags.Abilities_Summon= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"),FString ("召唤技能标签"));
   GameplayTags.Abilities_Fire_Firebolt= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"),FString ("火球技能标签"));
   GameplayTags.Abilities_Lightning_Electrocute= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"),FString ("电击技能标签"));
   
   //当前技能状态标签
   GameplayTags.Abilities_Status_Unlocked= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"),FString ("技能已解锁"));
   GameplayTags.Abilities_Status_Locked= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"),FString ("技能锁定"));
   GameplayTags.Abilities_Status_Eligible= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"),FString ("技能可解锁"));
   GameplayTags.Abilities_Status_Equipped= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"),FString ("技能已装备"));
   //当前技能类型标签
   GameplayTags.Abilities_Type_None= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"),FString ("空"));
   GameplayTags.Abilities_Type_Passive= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"),FString ("被动技能"));
   GameplayTags.Abilities_Type_Offensive= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"),FString ("攻击技能"));

   //DeBuff标签注册
   GameplayTags.DeBuff_Physical= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Physical"),FString ("物理负面效果 流血"));
   GameplayTags.DeBuff_Burn= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Burn"),FString ("火属性负面效果 燃烧"));
   GameplayTags.DeBuff_Arcane= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Arcane"),FString ("魔法负面效果"));
   GameplayTags.DeBuff_Stun= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Stun"),FString ("雷属性负面效果  眩晕"));
   //DeBuff配置标签
   GameplayTags.DeBuff_Chance= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Chance"),FString ("触发概率"));
   GameplayTags.DeBuff_Duration= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Duration"),FString ("持续时间"));
   GameplayTags.DeBuff_Damage= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Damage"),FString ("负面效果 伤害"));
   GameplayTags.DeBuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DeBuff.Frequency"),FString ("伤害触发间隔"));


   
   //技能冷却
   GameplayTags.Cooldown_Fire_FireBolt= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"),FString ("火球技能冷却"));
   GameplayTags.Cooldown_Lightning_Electrocute= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.Electrocute"),FString ("电击技能冷却"));
   
   //插槽武器
   GameplayTags.CombatSocket_Weapon= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),FString ("武器攻击"));
   GameplayTags.CombatSocket_RightHand= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),FString ("右手攻击"));
   GameplayTags.CombatSocket_LeftHand= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),FString ("左手攻击"));
   GameplayTags.CombatSocket_BothHands= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.BothHands"),FString ("双手攻击"));
   GameplayTags.CombatSocket_Ranged= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Ranged"),FString ("远程攻击"));
   GameplayTags.CombatSocket_Tail= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),FString ("尾部攻击"));

   //攻击动画蒙太奇
   GameplayTags.Montage_Attack_1= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"),FString ("攻击蒙太奇1"));
   GameplayTags.Montage_Attack_2= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"),FString ("攻击蒙太奇2"));
   GameplayTags.Montage_Attack_3= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"),FString ("攻击蒙太奇3"));
   GameplayTags.Montage_Attack_4= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"),FString ("攻击蒙太奇4"));

   //元属性
   GameplayTags.Attribute_Meta_IncomingXP= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Meta.IncomingXP"),FString ("经验值"));


   
   //属性和抗性标签一一匹配
   GameplayTags.DamageTypesToResistance.Add(GameplayTags.Attribute_Damage_Fire, GameplayTags.Attribute_Damage_Resistance_Fire);
   GameplayTags.DamageTypesToResistance.Add(GameplayTags.Attribute_Damage_Ice, GameplayTags.Attribute_Damage_Resistance_Ice);
   GameplayTags.DamageTypesToResistance.Add(GameplayTags.Attribute_Damage_Lightning, GameplayTags.Attribute_Damage_Resistance_Lightning);
   GameplayTags.DamageTypesToResistance.Add(GameplayTags.Attribute_Damage_Physical, GameplayTags.Attribute_Damage_Resistance_Physical);
   GameplayTags.DamageTypesToResistance.Add(GameplayTags.Attribute_Damage_Magic, GameplayTags.Attribute_Damage_Resistance_Magic);

   //负面标签和属性对应
   GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Attribute_Damage_Fire, GameplayTags.DeBuff_Burn);
   
   GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Attribute_Damage_Lightning, GameplayTags.DeBuff_Stun);
   GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Attribute_Damage_Physical, GameplayTags.DeBuff_Physical);
   GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Attribute_Damage_Magic, GameplayTags.DeBuff_Arcane);

   
   
}
