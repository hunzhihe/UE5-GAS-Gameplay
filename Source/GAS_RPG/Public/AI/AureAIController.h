// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AureAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAureAIController();
	

private:
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	// UPROPERTY()
	// TObjectPtr<UAIPerceptionComponent> PerceptionComponent;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
