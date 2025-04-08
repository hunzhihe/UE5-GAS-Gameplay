// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;
/**
 * 
 */
//存储技能信息的数据结构
USTRUCT(BlueprintType)
struct FAureAbilityInfo
{
	GENERATED_BODY()

	//解锁技能所需角色的等级
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelRequirement;

	//当前技能使用的技能类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;

	//技能标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
    //技能冷却标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();
	//技能类型标签（主动技能，被动技能）
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AbilityType = FGameplayTag();
	//技能输入映射标签
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
	//技能状态标签
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag = FGameplayTag();

	//技能图标
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	//背景材质
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;
};
UCLASS()
class GAS_RPG_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//技能数据数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	TArray<FAureAbilityInfo> AbilityInfo;

	//通过技能标签获取到技能信息
	FAureAbilityInfo GetAbilityInfoByTag(const FGameplayTag& AbilityTag, bool blogNotFound = false) const;
};
