// 关于GAS系统的学习


#include "AI/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *AIOwner->GetName());
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *ActorOwner->GetName());
	APawn* OwingPawn = AIOwner->GetPawn();
	
	const FName TargetTag = OwingPawn->ActorHasTag(FName("Player"))? FName("Enemy") : FName("Player");

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(OwingPawn, TargetTag, FoundActors);

	//遍历所有的角色，找到距离自己最近的角色
	float NearestDistance = TNumericLimits<float>::Max();
	AActor* NearestActor = nullptr;
	for (AActor* Actor : FoundActors)
	{
		float DistanceToActor = OwingPawn->GetDistanceTo(Actor);
		if (DistanceToActor < NearestDistance)
		{
			NearestDistance = DistanceToActor;
			NearestActor = Actor;
		}
	}

	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, NearestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, NearestDistance);
}
