// 关于GAS系统的学习


#include "AI/AureAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAureAIController::AAureAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	//在组件中添加视觉感知
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;//视野半径
	SightConfig->LoseSightRadius = 1500.0f;//视野失去半径
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;//视野角度
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;//是否检测敌人
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;//是否检测中立
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;//是否检测友方

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAureAIController::OnPerceptionUpdated);
}

void AAureAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	bool bPlayerFound = false;
	for (AActor* Actor : UpdatedActors)
	{
		//检测玩家
		if (Actor && Actor->ActorHasTag(FName("Player")))
		{
			//设置黑板中玩家信息
			Blackboard->SetValueAsObject(FName("Player"), Actor);
			bPlayerFound = true;
			break;

		}
	}
	if (!bPlayerFound)
	{
		Blackboard->ClearValue(FName("Player"));
	}
}
