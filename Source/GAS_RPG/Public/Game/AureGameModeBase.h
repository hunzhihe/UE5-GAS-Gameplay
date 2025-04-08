// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Date/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AureGameModeBase.generated.h"

class UAbilityInfo;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly,Category="Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;
};
