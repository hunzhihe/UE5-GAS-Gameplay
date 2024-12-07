// 关于GAS系统的学习


#include "AbilitySystem/AureAttributeSet.h"


#include "Net/UnrealNetwork.h"

UAureAttributeSet::UAureAttributeSet()
{
  InitShengMingZhi(100.f);
  InitMaxShengMingZhi(100.f);
  InitTiLiZhi(50.f);
  InitMaxTiLiZhi(50.f);
  
}

void UAureAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,ShengMingZhi,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MaxShengMingZhi,COND_None,REPNOTIFY_Always);

  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,TiLiZhi,COND_None,REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAureAttributeSet,MaxTiLiZhi,COND_None,REPNOTIFY_Always);
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


void UAureAttributeSet::OnRep_TiLiZhi(const FGameplayAttributeData& OldTiLiZhi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, TiLiZhi, OldTiLiZhi);
}

void UAureAttributeSet::OnRep_MaxTiLiZhi(const FGameplayAttributeData& OldMaxTiLiZhi) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAureAttributeSet, MaxTiLiZhi, OldMaxTiLiZhi);
}


