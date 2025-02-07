// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/AureProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AureGameplayTags.h"
#include "Actor/AureProjectile.h"
#include "Interaction/CombatInterface.h"

//#include "Kismet/KismetSystemLibrary.h"

void UAureProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	

	//UKismetSystemLibrary::PrintString(this, FString("ActivateAbility-C++"),true, true, FColor::Green, 5.0f);

// 	FTransform SpawnTransfrom;
// 	GetWorld()->SpawnActorDeferred<AAureProjectile>(ProjectileClass, SpawnTransfrom, GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
 }



void UAureProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer =GetAvatarActorFromActorInfo()->HasAuthority();//函数是否在服务器运行
	if(!bIsServer)return;
	

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.0f;
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
		//创建技能实例后，设置技能数据
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		//获取标签单例
        FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
		//依据等级获取伤害值
        const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel()) ;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("火球术伤害: %f"), ScaledDamage));
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attribute_Damage, ScaledDamage);
		
        Projectile->DamageEffectSpecHandle = SpecHandle;
		Projectile->FinishSpawning(SpawnTransfrom);
		
	}
}
