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
	//Enemy 接口
	virtual  void  HighlightActor() override;
	virtual  void  UnHighlightActor() override;

	//Enemy 接口结束

	virtual int32 GetLevel() override;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	virtual  void InitAbilityActorInfo() override;


    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Enemy")
	int32 Level = 1;
};
