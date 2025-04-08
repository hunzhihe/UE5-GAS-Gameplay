// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/ProjectileSpell__FireBolt.h"

#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "Actor/AureProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

void UProjectileSpell_FireBolt::SpawnProjectliles(const FVector& ProjectileTargetLocation,
                                                  const FGameplayTag& SocketTag, const FName SocketName, const bool bOverridePitch, const float PitchOverride,
                                                  AActor* HomingTarget)
{
	//判断此函数是否在服务器运行
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	//获取释放位置
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(), SocketTag);

	//限制产生火球的最大数量
	NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	//将方向转为旋转
	FRotator Rotation = (ProjectileTargetLocation-SocketLocation).Rotation();
	
	if (bOverridePitch)Rotation.Pitch = PitchOverride;//覆写发射角度

	//获取朝向向量
	const FVector Forward = Rotation.Vector();
	//根据函数获取到所有生成的转向
	TArray<FRotator> Rotators =UAureAbilitySysTEM_BFL::EvenlySpacedRotators(NumProjectiles, FVector::UpVector, Forward, ProjectileSpread);

		//遍历所有朝向，并生成火球
		for (FRotator& Rot : Rotators)
		{
                FTransform SpawnTransform;
				SpawnTransform.SetLocation(SocketLocation);
				SpawnTransform.SetRotation(Rot.Quaternion());

				//SpawnActorDeferred将异步创建实例，在实例创建完成时，相应的数据已经应用到了实例身上
				AAureProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAureProjectile>(
					ProjectileClass,
					SpawnTransform,
					GetOwningActorFromActorInfo(),
					Cast<APawn>(GetAvatarActorFromActorInfo()),
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			    //设置每个火球实例伤害
				Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

			   //根据目标类型设置HomingTargetCompinent,此内容必须飞弹被生成设置
                if (HomingTarget && HomingTarget->Implements<UCombatInterface>() )
                {
	                //设置攻击的位置为攻击对象的跟位置
                	Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
                }
                else
                {
	                //如果没有获取到攻击目标，则创建一个可销毁的并应用
                	HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
                	//设置组件位置
                	HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
                	Projectile->ProjectileMovement->HomingTargetComponent = HomingTargetSceneComponent;
                }

			    //设置飞弹朝向目标时的加速度
				Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
			    Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;//设置为真，则加速飞向攻击目标
			

				//确保变换设置被正确应用
				Projectile->FinishSpawning(SpawnTransform);
				// UKismetSystemLibrary::DrawDebugArrow(
				// 	GetAvatarActorFromActorInfo(),SocketLocation,
				// 	SocketLocation+Rot*100.0f,5,FLinearColor::Red,120,5);
		}
	
}

FString UProjectileSpell_FireBolt::GetDescription(int32 Level)
{
	return GetDescriptionAtLevel(Level, L"火球术");
}

FString UProjectileSpell_FireBolt::GetNextLevelDescription(int32 Level)
{
	return GetDescriptionAtLevel(Level, L"下一等级");
}

FString UProjectileSpell_FireBolt::GetDescriptionAtLevel(int32 Level, const FString& Title)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		//标题
		"<Title>%s</>\n"

		//细节
		"<Small>等级：</><Level>%i</>\n"
		"<Small>技能冷却：</><Cooldown>%.1f</>\n"
		"<Small>蓝量消耗：</><ManaCost>%.1f</>\n\n"

		//技能描述
		"<Default>发射%i个火球，在发生撞击时产生爆炸，并造成</><Damage>%i</><Default>点火焰伤害，并有一定几率燃烧。</>"),
        //动态修改值
		*Title,
		Level,
		Cooldown,
		ManaCost,
		FMath::Min(Level,NumProjectiles),
		ScaledDamage
		);
}
