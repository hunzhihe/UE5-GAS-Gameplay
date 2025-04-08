// 关于GAS系统的学习


#include "AbilitySystem/AureAttributeSet.h"

#include "Interaction/PlayerInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AureGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "GameFramework/Character.h"
#include "GAS_RPG/AureLogChannels.h"
#include "Interaction/CombatInterface.h"
//#include "Kismet/GameplayStatics.h"
#include "AureRPGAbilityTypes.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/AurePlayerController.h"
//#include "UI/WidgetController/AttributeMenuWidgetController.h"

UAureAttributeSet::UAureAttributeSet()
{
const FAureGameplayTags& Tags = FAureGameplayTags::Get();
  
  // FAttributeSiginature LiLiangDelegate;
  // LiLiangDelegate.BindStatic(GetLiLiangAttribute);
  


  // FAttributeSiginature ZhiLiDelegate;
  // ZhiLiDelegate.BindStatic(GetZhiLiAttribute);
  TagsToAttributes.Add(Tags.Attribute_Primary_LiLiang,GetLiLiangAttribute);
  TagsToAttributes.Add(Tags.Attribute_Primary_ZhiLi,GetZhiLiAttribute);
  TagsToAttributes.Add(Tags.Attribute_Primary_MinJie,GetMinJieAttribute);
  TagsToAttributes.Add(Tags.Attribute_Primary_NaiLi,GetNaiLiAttribute);

  /*
   * 添加属性
   */
  TagsToAttributes.Add(Tags.Attribute_Secondary_BaoJi,GetBaoJiAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_BaoJiDamage,GetBaoJiDamageAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_BaoJiResist,GetBaoJiResistAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_ChuanJia,GetChuanJiaAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_GeDang,GetGeDangAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_HuJia,GetHuJiaAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_MaxHealth,GetMaxShengMingZhiAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_MaxMana,GetMaxMonaAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_MonaRegener,GetMonaRegenerAttribute);
  TagsToAttributes.Add(Tags.Attribute_Secondary_ShengMingRegener,GetShengMingRegenerAttribute);


  TagsToAttributes.Add(Tags.Attribute_Damage_Resistance_Fire,GetResistanceFireAttribute);
  TagsToAttributes.Add(Tags.Attribute_Damage_Resistance_Ice,GetResistanceIceAttribute);
  TagsToAttributes.Add(Tags.Attribute_Damage_Resistance_Lightning,GetResistanceLightningAttribute);
  TagsToAttributes.Add(Tags.Attribute_Damage_Resistance_Physical,GetResistancePhysicalAttribute);
  TagsToAttributes.Add(Tags.Attribute_Damage_Resistance_Magic,GetResistanceMagicAttribute);
  
}

void UAureAttributeSet::SendXPEvent(const FEffectProperties& Properties)
{
  if (Properties.TargetCharacter->Implements<UCombatInterface>())
  {
    //从战斗接口获取等级和职业，通过蓝图函数获取可提供的经验值
    const int32 TargetLevel = ICombatInterface::Execute_GetLevel(Properties.TargetCharacter);
    const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Properties.TargetCharacter);
    const int32 XPReward = UAureAbilitySysTEM_BFL::GetXPRewardForClassAndLevel(Properties.TargetAvatarActor,TargetClass,TargetLevel);

    const FAureGameplayTags& Tags = FAureGameplayTags::Get();
    FGameplayEventData Payload;
    Payload.EventTag = Tags.Attribute_Meta_IncomingXP;
    Payload.EventMagnitude = XPReward;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Properties.SourceAvatarActor,Tags.Attribute_Meta_IncomingXP,Payload);
  }
}

void UAureAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);
  //主要属性
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,LiLiang,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ZhiLi,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MinJie,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,NaiLi,COND_None,REPNOTIFY_Always);
  
  //重要属性
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ShengMingZhi,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MaxShengMingZhi,COND_None,REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,Mona,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MaxMona,COND_None,REPNOTIFY_Always);

  //次要属性

  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,HuJia,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ChuanJia,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,GeDang,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,BaoJi,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,BaoJiDamage,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,BaoJiResist,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ShengMingRegener,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MonaRegener,COND_None,REPNOTIFY_Always);

  //抗性
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ResistanceFire, COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ResistanceIce, COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ResistanceLightning, COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ResistancePhysical, COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ResistanceMagic, COND_None,REPNOTIFY_Always);
  
}

// 属性改变预处理属性，例如生命值，法力值，不能高于最大值，死亡时不能低于0
void UAureAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
  Super::PreAttributeBaseChange(Attribute, NewValue);
  if (Attribute == GetShengMingZhiAttribute())
  {
    NewValue = FMath::Clamp(NewValue, 0.f, GetMaxShengMingZhi());
    
    //UE_LOG(LogTemp,Warning,TEXT("UAureAttributeSet::PreAttributeChange Health: %f") ,NewValue);
  }
  if (Attribute == GetMonaAttribute())
  {
    NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMona());
  }
}

// 显示伤害值
void UAureAttributeSet::ShowFloatText(const FEffectProperties& Properties, const float LocalIncomingDamage,bool IsBlockedHit, bool bIsCriticalHit)
{
  //调用显示伤害值
  if (Properties.SourceCharacter != Properties.TargetCharacter)
  {
    //从技能释放者获取玩家控制器
    if (AAurePlayerController* PC = Cast<AAurePlayerController>(Properties.SourceCharacter->Controller))
    {
      PC->ShowDamagedNumber(LocalIncomingDamage, Properties.TargetCharacter,IsBlockedHit,bIsCriticalHit);
    }
    //从目标获取玩家控制器
     if (AAurePlayerController* PC = Cast<AAurePlayerController>(Properties.TargetCharacter->Controller))
     {
       PC->ShowDamagedNumber(LocalIncomingDamage, Properties.TargetCharacter,IsBlockedHit,bIsCriticalHit);
     }
  }
}

//
void UAureAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{

  Super::PostGameplayEffectExecute(Data);                               

  FEffectProperties Properties;
  SetEffectProperties(Data, Properties);

  //判断当前目标是否已经死亡，如果死亡，将不再进行处理
  if (Properties.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Properties.TargetCharacter))
  {
    return;
  }
  
  if (Data.EvaluatedData.Attribute == GetShengMingZhiAttribute())
  {
    SetShengMingZhi(FMath::Clamp(GetShengMingZhi(), 0.f, GetMaxShengMingZhi()));
    UE_LOG(LogTemp,Warning,TEXT("UAureAttributeSet::PostGameplayEffectExecute Health: %f") ,GetShengMingZhi())
  }
  if (Data.EvaluatedData.Attribute == GetMonaAttribute())
  {
    SetMona(FMath::Clamp(GetMona(), 0.f, GetMaxMona()));
  }

  if (Data.EvaluatedData.Attribute == GetMetaIncomingDamageAttribute())
  {
    HandleIncomeingDamage( Properties);
  }
  
  if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
  {
    HandleIncomingXP(Properties);
  }
}

void UAureAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
  Super::PostAttributeChange(Attribute, OldValue, NewValue);
  //判断值是否改变
  if (!FMath::IsNearlyEqual(OldValue,NewValue))
  {
    if (Attribute == GetMaxShengMingZhiAttribute())
    {
      //获取当前的实际值
      const float CurrentValue = GetShengMingZhi();
      //获取到最大值变动后，按照比例修改后的值
      const float NewDelta = (OldValue>0)?(CurrentValue*NewValue/OldValue)-CurrentValue:NewValue;
      SetShengMingZhi(NewDelta+CurrentValue);
    }
    else if (Attribute == GetMaxMonaAttribute())
    {
      const float CurrentValue = GetMona();
      const float NewDelta = (OldValue>0)?(CurrentValue*NewValue/OldValue)-CurrentValue:NewValue;
      SetMona(NewDelta+CurrentValue);
    }
  }
}

void UAureAttributeSet::OnRep_ShengMingZhi(const FGameplayAttributeData& OldShengMingZhi) const
{
  //通知服务器，客户端正在复制一个属性值，并打算更改
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ShengMingZhi, OldShengMingZhi);
  
}
void UAureAttributeSet::OnRep_MaxShengMingZhi(const FGameplayAttributeData& OldMaxShengMingZhi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, MaxShengMingZhi, OldMaxShengMingZhi);
}

void UAureAttributeSet::OnRep_Mona(const FGameplayAttributeData& OldMona) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, Mona, OldMona);
}

void UAureAttributeSet::OnRep_MaxMona(const FGameplayAttributeData& OldMaxMona) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, MaxMona, OldMaxMona);
}

void UAureAttributeSet::OnRep_LiLiang(const FGameplayAttributeData& OldLiLiang) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, LiLiang, OldLiLiang);
}

void UAureAttributeSet::OnRep_ZhiLi(const FGameplayAttributeData& OldZhiLi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ZhiLi, OldZhiLi);
}

void UAureAttributeSet::OnRep_MinJie(const FGameplayAttributeData& OldMinJie) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, MinJie, OldMinJie);
}

void UAureAttributeSet::OnRep_NaiLi(const FGameplayAttributeData& OldNaiLi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, NaiLi, OldNaiLi);
}

void UAureAttributeSet::OnRep_HuJia(const FGameplayAttributeData& OldHuJia) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, HuJia, OldHuJia);
}

void UAureAttributeSet::OnRep_ChuanJia(const FGameplayAttributeData& OldChuanJia) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ChuanJia, OldChuanJia);
}

void UAureAttributeSet::OnRep_GeDang(const FGameplayAttributeData& OldGeDang) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, GeDang, OldGeDang);
}

void UAureAttributeSet::OnRep_BaoJi(const FGameplayAttributeData& OldBaoJi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, BaoJi, OldBaoJi);
}

void UAureAttributeSet::OnRep_BaoJiDamage(const FGameplayAttributeData& OldBaoJiDamage) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, BaoJiDamage, OldBaoJiDamage);
}

void UAureAttributeSet::OnRep_BaoJiResist(const FGameplayAttributeData& OldBaoJiResist) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, BaoJiResist, OldBaoJiResist);
}

void UAureAttributeSet::OnRep_ShengMingRegener(const FGameplayAttributeData& OldShengMingRegener) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ShengMingRegener, OldShengMingRegener);
}

void UAureAttributeSet::OnRep_MonaRegener(const FGameplayAttributeData& OldMonaRegener) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, MonaRegener, OldMonaRegener);
}

void UAureAttributeSet::OnRep_ResistanceFire(const FGameplayAttributeData& OldResistanceFire) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ResistanceFire, OldResistanceFire);
}

void UAureAttributeSet::OnRep_ResistanceIce(const FGameplayAttributeData& OldResistanceIce) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ResistanceIce, OldResistanceIce);
}

void UAureAttributeSet::OnRep_ResistanceLightning(const FGameplayAttributeData& OldResistanceLightning) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ResistanceLightning, OldResistanceLightning);
}

void UAureAttributeSet::OnRep_ResistanceMagic(const FGameplayAttributeData& OldResistanceMagic) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ResistanceMagic, OldResistanceMagic);
}

void UAureAttributeSet::OnRep_ResistancePhysical(const FGameplayAttributeData& OldResistancePhysical) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, ResistancePhysical, OldResistancePhysical);
}

void UAureAttributeSet::HandleIncomeingDamage(const FEffectProperties& Properties)
{
  const float LocalIncomingDamage = GetMetaIncomingDamage();
  SetMetaIncomingDamage(0.f);
  if (LocalIncomingDamage > 0.f)
  {
    const float NewHealth = GetShengMingZhi() - LocalIncomingDamage;
    SetShengMingZhi(FMath::Clamp(NewHealth, 0.f, GetMaxShengMingZhi()));

    //血量小于等于0时，死亡
    const bool bFatal = NewHealth <= 0.f;
    if (bFatal)
    {
      //角色死亡时，调用死亡逻辑
      ICombatInterface* CombatInterface = Cast<ICombatInterface>(Properties.TargetAvatarActor);
      if (CombatInterface)
      {
        CombatInterface->Die(UAureAbilitySysTEM_BFL::GetDeathImpulse(Properties.EffectContextHandle));
      }
      //死亡时，发送经验事件
      SendXPEvent(Properties);
    }
    else
    {
      //角色未死亡时，激活受击技能效果
      FGameplayTagContainer TagContainer;
      TagContainer.AddTag(FAureGameplayTags::Get().Effects_HitReact);
      //应用受击前，先取消之前的受击效果，在尝试激活新的受击效果
      Properties.TargetASC->CancelAbilities(&TagContainer);
      Properties.TargetASC->TryActivateAbilitiesByTag(TagContainer);
    }
    //获取格挡和暴击
    const bool IsBlockedHit = UAureAbilitySysTEM_BFL::IsBlockedHit(Properties.EffectContextHandle);
    const bool bIsCriticalHit = UAureAbilitySysTEM_BFL::IsCriticalHit(Properties.EffectContextHandle);
    ShowFloatText(Properties, LocalIncomingDamage,IsBlockedHit,bIsCriticalHit);

    //判断当前是否应用负面效果
    if (UAureAbilitySysTEM_BFL::IsDeBuffApplied(Properties.EffectContextHandle))
    {
      HandleDeBuff(Properties);
    }
    //设置攻击击退效果
    const FVector& KnockbackForceDirection = UAureAbilitySysTEM_BFL::GetKnockbackForceDirection(Properties.EffectContextHandle);
    if (!KnockbackForceDirection.IsNearlyZero(1.0f))//如果击退的值不接近于0，则触发击退效果
    {
      Properties.TargetCharacter->LaunchCharacter(KnockbackForceDirection, true, true);
    }
  }
  
}

void UAureAttributeSet::HandleIncomingXP(const FEffectProperties& Properties)
{
  const float LocalIncomingExperience = GetIncomingXP();
  SetIncomingXP(0);

  //UE_LOG(LogAure,Log,TEXT("获取传入经验：%f"), LocalIncomingExperience)
    
  //查看当经验传入时是否会升级
  //将经验应用给自身
  if (Properties.SourceCharacter->Implements<UPlayerInterface>())
  {
    //获取角色当前等级和经验
    const int32 CurrentLevel = ICombatInterface::Execute_GetLevel(Properties.SourceCharacter);
    const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Properties.SourceCharacter);

    //获取获得的经验后的新等级
    const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Properties.SourceCharacter, CurrentXP + LocalIncomingExperience);
    const int32 NumLevelUps = NewLevel - CurrentLevel; //查看等级是否有变化

    if (NumLevelUps>0)
    {
      for (int32 i = CurrentLevel; i<NewLevel; i++)
      {
        //获取升级提供的技能点和属性点
        int32 AttributePointsReward = IPlayerInterface::Execute_GetAttributePoints(Properties.SourceCharacter, CurrentLevel);
        int32 SkillPointsReward = IPlayerInterface::Execute_GetSkillPoints(Properties.SourceCharacter, CurrentLevel);

        //提升等级，增加角色技能点和属性点
         
        IPlayerInterface::Execute_AddToAttributePoints(Properties.SourceCharacter, AttributePointsReward);
        IPlayerInterface::Execute_AddToSkillPoints(Properties.SourceCharacter, SkillPointsReward);
      }
         

      //升级和升级效果
      IPlayerInterface::Execute_AddToPlayerLevel(Properties.SourceCharacter, NumLevelUps);
      IPlayerInterface::Execute_LevelUp(Properties.SourceCharacter);

      //升级时，补满状态
      SetMona(GetMaxMona());
      SetShengMingZhi(GetMaxShengMingZhi());
         
    }
    IPlayerInterface::Execute_AddToXP(Properties.SourceCharacter, LocalIncomingExperience);
  }
}

void UAureAttributeSet::HandleDeBuff(const FEffectProperties& Properties)
{
  //-------实现设置GE，并应用到角色身上，可蓝图，也可C++，这里使用c++
  //获取负面效果相关参数
  const FGameplayTag DeBuffType = UAureAbilitySysTEM_BFL::GetDeBuffDamageType(Properties.EffectContextHandle);
  const float DeBuffDamage = UAureAbilitySysTEM_BFL::GetDeBuffDamage(Properties.EffectContextHandle);
  const float DeBuffDuration = UAureAbilitySysTEM_BFL::GetDeBuffDuration(Properties.EffectContextHandle);
  const float DeBuffFrequency = UAureAbilitySysTEM_BFL::GetDeBuffFrequency(Properties.EffectContextHandle);

  //创建GE使用名称，并创建一个可实例化的GE
  FString DeBuffName = FString::Printf(TEXT("DynamicDeBuff_%s"),*DeBuffType.ToString());
  UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(),FName(DeBuffName));

  //设置动态创建GE的属性
  Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;//有时间限制
  Effect->DurationMagnitude = FScalableFloat(DeBuffDuration);//设置持续时间
  Effect->Period = FScalableFloat(DeBuffFrequency);//设置GE的触发策略，间隔时间
  Effect->PeriodicInhibitionPolicy = ::EGameplayEffectPeriodInhibitionRemovedPolicy::NeverReset;//设置每次应用后不会重置触发时间
  //设置可叠加层数
  Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
  Effect->StackLimitCount = 1;//设置可叠加层数
  Effect->StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;//在应用后重置，重置持续时间
  Effect->StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication;//在应用时，触发重置Period时间
  Effect->StackExpirationPolicy = EGameplayEffectStackingExpirationPolicy::ClearEntireStack;//GE时间到了默认清除所有层数，也可以清除单层的
  Effect->bDenyOverflowApplication = true;//叠加层数超过时，将不会刷新GE实例
  Effect->bClearStackOnOverflow = true;//叠加层数超过时，将清除GE；

  //通过GE组件来设置标签
  UTargetTagsGameplayEffectComponent& TargetTagsGameplayEffectComponent = Effect->AddComponent<UTargetTagsGameplayEffectComponent>();
  FInheritedTagContainer InheritableOwnedTagsContainer;//获取组件标签容器
  InheritableOwnedTagsContainer.Added.AddTag(DeBuffType);//添加标签
  TargetTagsGameplayEffectComponent.SetAndApplyTargetTagChanges(InheritableOwnedTagsContainer);//应用更新

  //设置属性修改
  const int32 Index = Effect->Modifiers.Num();//获取当前属性修改的Modifiers的长度，也就是下一个添加的Modify的下标索引
  Effect->Modifiers.Add(FGameplayModifierInfo());//添加一个新的Modify
  FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];//通过下标索引获取到Modify

  ModifierInfo.ModifierMagnitude = FScalableFloat(DeBuffDamage);//设置应用的属性值
  ModifierInfo.ModifierOp = EGameplayModOp::Additive;//设置属性运算符号
  ModifierInfo.Attribute = UAureAttributeSet::GetMetaIncomingDamageAttribute();//设置要修改的属性

  //创建GE实例，并添加伤害类型标签，应用GE
  FGameplayEffectContextHandle EffectContextHandle = Properties.SourceASC->MakeEffectContext();
  EffectContextHandle.AddSourceObject(Properties.SourceAvatarActor);
  if (const FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect,EffectContextHandle,1.f))
  {
    FAureRPGGameplayEffectContext* AureContext = static_cast<FAureRPGGameplayEffectContext*>(MutableSpec->GetContext().Get());
    const TSharedPtr<FGameplayTag> DeBuffDamageType = MakeShareable(new FGameplayTag(DeBuffType));
    AureContext->SetDeBuffDamageType(DeBuffDamageType);

    Properties.TargetASC->ApplyGameplayEffectSpecToSelf( *MutableSpec);
  }
  
}

// 设置属性效果，处理来源和目标的属性
// 该函数 `SetEffectProperties` 用于设置效果属性，主要处理来源和目标的属性。具体步骤如下：
// 1. 设置效果上下文。
// 2. 获取并验证来源的 AbilitySystemComponent (ASC)，并获取其关联的 AvatarActor 和 Controller。
// 3. 如果来源 Controller 为空且 AvatarActor 是 Pawn，则尝试从 Pawn 获取 Controller。
// 4. 如果来源 Controller 不为空，则获取其关联的 Character。
// 5. 验证并设置目标的 AvatarActor、Controller、Character 和 ASC。
void UAureAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& EffectProperties)
{
  EffectProperties.EffectContextHandle =  Data.EffectSpec.GetContext();
  
  EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();


  if (IsValid(EffectProperties.SourceASC)&&EffectProperties.SourceASC->AbilityActorInfo.IsValid()&&EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
  {
    EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->GetAvatarActor();
    EffectProperties.SourceController= EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();

    if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor !=nullptr)
    {
      if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
      {
        EffectProperties.SourceController = Pawn->GetController();
      }
    }
    if (EffectProperties.SourceController != nullptr)
    {

      EffectProperties.SourceCharacter = EffectProperties.SourceController->GetCharacter();
    }
  }
  if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
  {
    EffectProperties.TargetAvatarActor = Data.Target.GetAvatarActor();
    EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
    EffectProperties.TargetCharacter =  Cast<ACharacter>(EffectProperties.TargetAvatarActor);
    EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
  }
}


