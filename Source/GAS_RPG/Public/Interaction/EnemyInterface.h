// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_RPG_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//两个纯虚函数，在子类中定义，用来高亮显示敌人
	virtual  void  HighlightActor() = 0;
	virtual  void  UnHighlightActor() = 0;
   //  设置和获取战斗目标
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyInterface")
	void SetCombatTarget(AActor* CombatTarget);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyInterface")
	AActor* GetCombatTarget() const;

	
};
