// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Character/AureBaseCharacter.h"
#include "AureCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureCharacter : public AAureBaseCharacter
{
	GENERATED_BODY()

public:
	AAureCharacter();

	virtual  void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual  int32 GetLevel() override;
private:
	virtual  void InitAbilityActorInfo() override;
	
};
