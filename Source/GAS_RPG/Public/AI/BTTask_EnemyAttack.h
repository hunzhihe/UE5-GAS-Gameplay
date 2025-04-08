// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UBTTask_EnemyAttack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
