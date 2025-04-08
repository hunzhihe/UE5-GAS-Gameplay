// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Date/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//#include "UI/WidgetController/OverlayWidgetController.h"
#include "AureAbilitySysTEM_BFL.generated.h"

class UOverlayWidgetController;
struct FDamageEffectParams;
class UAbilityInfo;
class AAureHUD;
class USpellMenuWidgetController;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureAbilitySysTEM_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject,FWidgetControllerParams& WidgetControllerParams,AAureHUD*& OutAureHUD);
	
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController",meta=(DefaultToSelf = "WorldContextObject"))
	static  UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	//获取属性菜单控制器
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static  UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);
	

	
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* AbilitySystemComponent);

	// 给角色初始化角色技能
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject,UAbilitySystemComponent* AbilitySystemComponent,ECharacterClass CharacterClass);
	//获取角色配置数据
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	// 判断当前GE是否格挡
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContext);
	//判断当前GE是否暴击
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContext);
	//设置当前GE是否格挡
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffects")
	static void SetBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContext,const bool bInBlockedHit);
	//设置当前GE是否暴击
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffects")
	static void SetCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContext,const bool bInCriticalHit);

	//获取攻击位置半径内的所有动态碰撞体
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayerWithRadius(const UObject* WorldContextObject,TArray<AActor*>& OutOverlappingActors,const TArray<AActor*>& ActorsToIgnore,float Radius,const FVector& SphereOrigin);

	//获取双方是否在为敌对势力
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayMechanics")
	static bool IsEnemy(const AActor* ActorA,const AActor* ActorB);

	//获取根据敌人类型和等级获取敌人产生的经验
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|CharacaterClassDefaults")
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject,ECharacterClass CharacterClass,int32 Level);

	//获取玩家的角色技能配置数据
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|AbilityInfo")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	//通过技能生成的负面配置项应用技能负面效果
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);


	//获取当前GE是否成功应用负面效果
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static bool IsDeBuffApplied(const FGameplayEffectContextHandle& EffectContext);
	//获取当前GE负面效果伤害
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static float GetDeBuffDamage(const FGameplayEffectContextHandle& EffectContext);
	//获取当前GE负面效果持续时间
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static float GetDeBuffDuration(const FGameplayEffectContextHandle& EffectContext);
	//获取当前GE负面效果频率
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static float GetDeBuffFrequency(const FGameplayEffectContextHandle& EffectContext);
	//获取当前GE负面效果伤害类型
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static FGameplayTag GetDeBuffDamageType(const FGameplayEffectContextHandle& EffectContext);

	//设置当前GE是否成功应用负面效果
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffect")
	static void SetDeBuffApplied(UPARAM(ref) FGameplayEffectContextHandle& EffectContext,const bool bInDeBuffApplied);
	//设置GE负面效果相关数值，负面效果伤害类型 伤害值 持续时间 频率
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffect")
	static void SetDeBuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContext,FGameplayTag& InDamageType,float InDeBuffDamage,float InDeBuffDuration,float InDeBuffFrequency);

	//获取当前GE死亡冲击的方向和力度
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContext);
	//设置当前GE死亡冲击的方向和力度
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(
		UPARAM(ref) FGameplayEffectContextHandle& EffectContext,const FVector& InDeathImpulse);

	//获取当前GE攻击击退力方向和力度
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static FVector GetKnockbackForceDirection(const FGameplayEffectContextHandle& EffectContext);
	//设置当前GE攻击击退力方向和力度
	UFUNCTION(BlueprintCallable,Category="AureAbilitySystemLibrary|GameplayEffect")
	static void SetKnockbackForceDirection(
		UPARAM(ref) FGameplayEffectContextHandle& EffectContext,const FVector& InKnockbackForceDirection);

	/*该函数根据传入的值计算均匀分布的多段角度
	 *
	 * @param NumRotators 分段数
	 * @param Axis 基于旋转的轴
	 * @param Forword  正前方向
	 * @param Speard 角度范围
	 *
	 * @return  TArray<FRotator&> 返回每段角度的中间的数组
	 *
	 *
	 * @note 该函数用于在技能生成投掷物的函数逻辑中
	 */
	UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static TArray<FRotator> EvenlySpacedRotators(int32 NumRotators,const FVector& Axis,const FVector& Forword,float Speard);

	/*该函数根据传入的值计算均匀分布的多段角度
 *
 * @param NumVectors 分段数
 * @param Axis 基于旋转的轴
 * @param Forword  正前方向
 * @param Speard 角度范围
 *
 * @return  TArray<FVector&> 返回每段角度的中间角度的朝向数组
 *
 *
 * @note 该函数用于在技能生成投掷物的函数逻辑中
 */
    UFUNCTION(BlueprintPure,Category="AureAbilitySystemLibrary|GameplayEffect")
	static TArray<FVector> EvenlyRotatedVectors(int32 NumVectors,const FVector& Axis,const FVector& Forword,float Speard);


	
	
};
