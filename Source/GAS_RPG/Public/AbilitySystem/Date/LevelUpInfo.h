// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

/**
 * 
 */
//角色升级数据结构体
USTRUCT(BlueprintType)
struct FAureLevelUpInfo
{
	GENERATED_BODY()

	//等级上升所需经验
	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	//升级时奖励的属性点值
	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	//升级时做奖励的可分配技能点数
	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};
UCLASS()
class GAS_RPG_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//当前所有等级的升级数据
	UPROPERTY(EditDefaultsOnly)
	TArray<FAureLevelUpInfo> LevelUpInfomation;
    //通过经验值获取角色等级
	int32 FindLeveForXP(int32 XP) const;
};
