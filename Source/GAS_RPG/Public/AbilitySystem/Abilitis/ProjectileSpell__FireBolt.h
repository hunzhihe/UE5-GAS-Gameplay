// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilitis/AureProjectileSpell.h"
#include "ProjectileSpell__FireBolt.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UProjectileSpell_FireBolt : public UAureProjectileSpell
{
	GENERATED_BODY()
public:
	
	//生成多段火球的函数
	UFUNCTION(BlueprintCallable,Category = "Projectile")
	void SpawnProjectliles(const FVector& ProjectileTargetLocation,
		const FGameplayTag& SocketTag,const FName SocketName,const bool bOverridePitch = false,
		const float PitchOverride = 0.0f, AActor* HomingTarget = nullptr
		);
	
	//获取火球术描述，，重载
	virtual FString GetDescription(int32 Level) override;
	//获取下一等级描述，，重载
	virtual FString GetNextLevelDescription(int32 Level) override;

	FString GetDescriptionAtLevel(int32 Level, const FString& Title);


protected:
	//攻击角度
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	float ProjectileSpread = 90.f;
    //最大生成火球数量
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	int32 MaxNumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	float HomingAccelerationMin = 1600.f;
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	float HomingAccelerationMax = 2000.f;
	UPROPERTY(EditDefaultsOnly,Category = "Projectile")
	bool bLaunchHomingProjectiles = true;//是否生成追踪火球
};
