// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AbilitySystemInterface.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
//#include "Interaction/EnemyInterface.h"
#include "AureBaseCharacter.generated.h"

class UDeBuffNiagaraComponent;
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class GAS_RPG_API AAureBaseCharacter : public ACharacter ,public IAbilitySystemInterface ,public ICombatInterface
{
	GENERATED_BODY()
public:
	
	
	AAureBaseCharacter();

	FOnASCRegistered OnAscRegistered;//ASC注册成功委托
	FOnDeath OnDeath;//角色死亡委托
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet()const {return AttributeSet;}

	
	virtual void BeginPlay() override;
	
    bool bDead = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	//-----ICombatInterface-----
	//角色死亡函数覆写
	virtual void Die(const FVector& DeathImpulse) override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) const override;
	virtual bool IsDead_Implementation() const override;
	virtual  AAureBaseCharacter* GetAvatar_Implementation()  override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& TagMontages)override;
	virtual int32 GetMinionsCount_Implementation() override;
	virtual void IncrementMinionsCount_Implementation(const int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;//获取到ASC注册成功委托
	virtual FOnDeath& GetOnDeathDelegate() override;
	
	//--------ICombatInterface结束-----

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	
	//可用于设置多个基础攻击动画
	UPROPERTY(EditAnywhere,Category="Combat")
	TArray<FTaggedMontage> AttackMontages;
	
	//指针变量：武器组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName LeftHandSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName TailSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundBase* DeathSound;
	//受伤特效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NiagaraSystem")
	UNiagaraSystem* BloodEffect;

	//火焰负面效果表现组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDeBuffNiagaraComponent> BurnDeBuffNiagaraComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void  InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//重要属性（生命 魔法）
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const;
	
	virtual  void InitializeDefaultAttributes() const;

	void InitializeAbilities() const;


	//溶解函数
	void UpdateDissolve();

	//溶解时间线,蓝图中实现
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* MaterialInstanceDynamic);
	
	//武器溶解时间线,蓝图中实现
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* MaterialInstanceDynamic);
	//声明材质实例
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	//召唤物数量
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	int32 MinionsCount=0;
private:
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility> > Abilities;

	//被动技能设置
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility> > StartupPassiveAbilities;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;




	



};
