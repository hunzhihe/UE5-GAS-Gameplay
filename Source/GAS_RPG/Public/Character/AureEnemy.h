// 关于GAS系统的学习

#pragma once
  
#include "CoreMinimal.h"
#include "AbilitySystem/Date/CharacterClassInfo.h"
#include "AI/AureAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/AureBaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AureEnemy.generated.h"

class UWidgetComponent;
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

	
	virtual AActor* GetCombatTarget_Implementation() const override;
	virtual  void SetCombatTarget_Implementation(AActor* InCombatTarget)  override;
	//Enemy 接口结束

	/*--------- ICombatInterface战斗接口---------------*/
	virtual int32 GetLevel_Implementation() override;
	    //敌人角色死亡函数覆写
	virtual void Die(const FVector& DeathImpulse) override;
	/*---------- ICombatInterface战斗接口--------------*/
	//将在Pawn被控制器（PlayerController和AIController都行）控制时触发回调
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnShengMingzhiChanged;


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHpChanged;

	// 是否处于被攻击
	UPROPERTY(BlueprintReadOnly,Category = "Combat" )
	bool bHitReacting = false;
	//角色最大移动速度
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Combat" )
	float BaseWalkSpeed = 250.0f;

	void HitReactTagChanged(const FGameplayTag Tag, int32 NewCount);

	//死亡角色消失时间
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Combat")
	float lifeSpan = 5.0f;



	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	virtual  void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	


    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Enemy")
	int32 Level = 1;



	//敌人生命条
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Enemy")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<AAureAIController> AureAIController;
	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;;
};
