// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/AureProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AureGameplayTags.h"
#include "Actor/AureProjectile.h"

#include "Interaction/CombatInterface.h"

//#include "Kismet/KismetSystemLibrary.h"

FString UAureProjectileSpell::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("FireBolt"));
}
FString UAureProjectileSpell::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("FireBolt"));
}

void UAureProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	

	//UKismetSystemLibrary::PrintString(this, FString("ActivateAbility-C++"),true, true, FColor::Green, 5.0f);

// 	FTransform SpawnTransfrom;
// 	GetWorld()->SpawnActorDeferred<AAureProjectile>(ProjectileClass, SpawnTransfrom, GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
 }



void UAureProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer =GetAvatarActorFromActorInfo()->HasAuthority();//函数是否在服务器运行
	if(!bIsServer)return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
		
		FTransform SpawnTransfrom;
		SpawnTransfrom.SetLocation(SocketLocation);
		//技能角度
		SpawnTransfrom.SetRotation(Rotation.Quaternion());
		//异步创建技能实例，保证创建的技能实例和相应数据是同步的
		AAureProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAureProjectile>(
			ProjectileClass,
			SpawnTransfrom,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		//  //创建技能实例后，设置技能数据
		//  const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
		//  //生成技能效果上下文句柄
        //FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		//
		//  EffectContextHandle.SetAbility(this);//设置技能
		//  EffectContextHandle.AddSourceObject(Projectile);//设置技能效果的源对象
		// // //添加Actor
		//  TArray<TWeakObjectPtr<AActor>> Actors;
		//  Actors.Add(Projectile);
		//  EffectContextHandle.AddActors(Actors);
		//  //添加命中效果
		//  FHitResult HitResult;
		//  HitResult.Location = ProjectileTargetLocation;
		//  EffectContextHandle.AddHitResult(HitResult);
		//  //添加技能触发位置
		//  EffectContextHandle.AddOrigin(ProjectileTargetLocation);
		//
		//  const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
  //
		//  //获取标签单例
  //        FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
		//  //依据等级获取伤害值
		//  // for (auto& Pair :DamageTypes)
		//  // {
		//  // 	const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel()) ;
		//  // 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("火球术伤害: %f"), ScaledDamage));
		//  // 	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
		//  // }
		// const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel()) ;
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("火球术伤害: %f"), ScaledDamage));
		// UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageType, ScaledDamage);
  //        
		//
		// Projectile->DamageEffectSpecHandle = SpecHandle;
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->FinishSpawning(SpawnTransfrom);
		
	
}
