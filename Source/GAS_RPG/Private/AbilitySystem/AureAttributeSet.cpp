// 关于GAS系统的学习


#include "AbilitySystem/AureAttributeSet.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "AureGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/AurePlayerController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

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
   *
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
  
}

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

void UAureAttributeSet::ShowFloatText(FEffectProperties Properties, const float LocalIncomingDamage) const
{
  if (Properties.SourceCharacter != Properties.TargetCharacter)
  {
    if (AAurePlayerController* PC = Cast<AAurePlayerController>(UGameplayStatics::GetPlayerController(Properties.SourceCharacter, 0)))
    {
      PC->ShowDamagedNumber(LocalIncomingDamage, Properties.TargetCharacter);
    }
  }
}

void UAureAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
  Super::PostGameplayEffectExecute(Data);                               

  FEffectProperties Properties;
  SetEffectProperties(Data, Properties);

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
    const float LocalIncomingDamage = GetMetaIncomingDamage();
    SetMetaIncomingDamage(0.f);
    if (LocalIncomingDamage > 0.f)
    {
      const float NewHealth = GetShengMingZhi() - LocalIncomingDamage;
      SetShengMingZhi(FMath::Clamp(NewHealth, 0.f, GetMaxShengMingZhi()));

      //血量小于等于0时，死亡
      const bool bFatal = NewHealth <= 0.f;
      if (!bFatal)
      {
        //角色未死亡时，激活受击技能效果
        FGameplayTagContainer TagContainer;
        TagContainer.AddTag(FAureGameplayTags::Get().Effects_HitReact);
        Properties.TargetASC->TryActivateAbilitiesByTag(TagContainer);
      }
      else
      {
        //角色死亡时，调用死亡逻辑
        ICombatInterface* CombatInterface = Cast<ICombatInterface>(Properties.TargetAvatarActor);
        if (CombatInterface)
        {
          CombatInterface->Die();
        }
      }
      ShowFloatText(Properties, LocalIncomingDamage);
    }
  }
  //  const FGameplayEffectContextHandle EffectContextHandle=   Data.EffectSpec.GetContext();
  //
  // const UAbilitySystemComponent* SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
  //
  //
  // if (IsValid(SourceASC)&&SourceASC->AbilityActorInfo.IsValid()&&SourceASC->AbilityActorInfo->AvatarActor.IsValid())
  // {
  //   AActor* SourceAvatarActor = SourceASC->GetAvatarActor();
  //   const AController* SourceController= SourceASC->AbilityActorInfo->PlayerController.Get();
  //
  //   if (SourceController == nullptr && SourceAvatarActor !=nullptr)
  //   {
  //     if (const APawn* Pawn = Cast<APawn>(SourceAvatarActor)())
  //     {
  //       SourceController = Pawn->GetController();
  //     }
  //   }
  //   if (SourceController != nullptr)
  //   {
  //
  //     ACharacter* SourceCharacter = SourceController->GetCharacter();
  //     
  //   }
  //   
  // }
  // if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
  // {
  //   AActor* TargetAvatarActor = Data.Target.GetAvatarActor();
  //   AController* TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
  //   ACharacter* TargetCharacter =  Cast<ACharacter>(TargetAvatarActor);
  //   UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
  //
  //
  //   
  // }
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

void UAureAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& EffectProperties)
{
  EffectProperties.EffectContextHandle=   Data.EffectSpec.GetContext();
  
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


