// 关于GAS系统的学习


#include "AbilitySystem/Abilitis/SummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"


TArray<FVector> USummonAbility::GetSpawnLocations()
{
	//获取角色的朝向
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	//获取角色的位置
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	//将召唤区域分段
	const float DeltaSpread = SpawnSpread/NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread*i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction*FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation+ FVector(0,0,400.f), ChosenSpawnLocation - FVector(0,0,400.f), ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
		//DrawDebugSphere(GetWorld(),ChosenSpawnLocation, 10, 8, FColor::Green, false, 3.f);
		
		//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction*MaxSpawnDistance, 4, FLinearColor::Red, 3.f);
		//DrawDebugSphere(GetWorld(),Location+Direction*MaxSpawnDistance, 5, 8, FColor::Red, false, 3.f);
		//DrawDebugSphere(GetWorld(),Location+Direction*MinSpawnDistance, 5, 8, FColor::Red, false, 3.f);
	}

	
	return SpawnLocations;
}

TSubclassOf<APawn> USummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num()-1);
	return MinionClasses[Selection];
}
