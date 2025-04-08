// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_RPG_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    //根据经验获取等级
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	int32 FindLevelForXP(int32 InXP) const;
	//获取当前经验值
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	int32 GetXP() const;
	//获取属性点奖励
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	int32 GetAttributePoints(int32 Level) const;
	//获取技能点奖励
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	int32 GetSkillPoints(int32 Level) const;
	//增加经验
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	void AddToXP(int32 InXP);
	//增加等级
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	void AddToPlayerLevel(int32 InPlayerLevel);
	//增加属性点
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	void AddToAttributePoints(int32 InAttributePoints);
	//增加技能点
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	void AddToSkillPoints(int32 InSkillPoints);
	//升级
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	void LevelUp();
	//获取可分配属性点数
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerInterface")
	int32 GetAttributesPoints() const;
};
