// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "SummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API USummonAbility : public UAureGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category="Summoning")
	TArray<FVector> GetSpawnLocations();
	UFUNCTION(BlueprintPure, Category="Summoning")
    TSubclassOf<APawn>GetRandomMinionClass();//获取随机召唤类
    UPROPERTY(EditAnywhere,Category="Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditAnywhere,Category="Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float MinSpawnDistance = 50.f;
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float SpawnSpread = 90.f;
};
