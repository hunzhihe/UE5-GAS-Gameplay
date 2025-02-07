// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Date/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AureGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditDefaultsOnly,Category="Chaeacter Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
