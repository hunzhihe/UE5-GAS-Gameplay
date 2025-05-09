// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UBTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()

    protected:
        virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetToFollowSelector;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DistanceToTargetSelector;;
	
	
};
