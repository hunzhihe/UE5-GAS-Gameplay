// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AureProjectile.generated.h"

//struct FGameplayEffectSpecHandle;
class UNiagaraSystem;
class USphereComponent;

UCLASS()
class GAS_RPG_API AAureProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAureProjectile();

	//创建一个发射组件，用于控制投射物的移动，例如子弹或魔法球，负责处理投射物的速度，加速度，路径
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	//发射物击中特效
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	//发射物击中音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	//飞行中的音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> FlightLoopSound;
	//储存循环音效的变量，后续用于删除
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopSoundComponent;

	UPROPERTY(BlueprintReadOnly,meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
	//增加对应的碰撞检测回调
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	//碰撞体
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;

	bool bHasHit;

	//播放相关特效和声音
	void PlayEffects() const;

};
