// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/Date/CharacterClassInfo.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*);//Actor初始化完成后委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath,AActor*,DeadActor);//Actor死亡后委托

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()
	//使用的动画
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;
	//对应的标签
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag MontageTag;

	//攻击时的触发伤害的骨骼插槽
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag SocketTag;//技能释放位置

	//攻击时击中的音效
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_RPG_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//获取玩家等级
    UFUNCTION(BlueprintNativeEvent)
	int32 GetLevel();

	//获取技能释放位置，通过蓝图实现
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag) const;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatSocketLocationByStruct(const FTaggedMontage& MontageTag) const;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void FaceingTarget(const FVector& TargetLocation);
   //获取被攻击动画
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
	//角色死亡逻辑函数
	virtual void Die( const FVector& DeathImpulse) = 0;

	//多播角色死亡逻辑
	//当前角色是否死亡
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "ICombatInterface")
	bool IsDead() const;

	//获取当前角色
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	AActor* GetAvatar() ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	TArray<FTaggedMontage> GetAttackMontages();

	//获取受伤特效
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "ICombatInterface")
	UNiagaraSystem* GetBloodEffect();

	//通过标签从结构体数组中获取对应结构体
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& TagMontages);

	//获取角色拥有的召唤物数量
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	int32 GetMinionsCount();

	//增加召唤物数量
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	void IncrementMinionsCount(const int32 Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ICombatInterface")
	ECharacterClass GetCharacterClass();


	//获取Actor初始化完成后的委托
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate()=0;

	
	virtual FOnDeath& GetOnDeathDelegate()=0;//获取Actor死亡后的委托
};
