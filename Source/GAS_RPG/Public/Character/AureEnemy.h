// 关于GAS系统的学习

#pragma once
  
#include "CoreMinimal.h"
#include "Character/AureBaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AureEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureEnemy : public AAureBaseCharacter ,public  IEnemyInterface
{
	GENERATED_BODY()

public:
	AAureEnemy();
	virtual  void  HighlightActor() override;
	virtual  void  UnHighlightActor() override;


	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
};
