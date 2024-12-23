// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "AurePlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct  FInputActionValue;
class IEnemyInterface;
UCLASS()
class GAS_RPG_API AAurePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAurePlayerController();
	virtual  void PlayerTick(float DeltaTime) override;

	
protected:
	virtual  void BeginPlay() override;

	//设置玩家输入组件
	virtual  void SetupInputComponent() override;

private:
	//创建储存输入映射上下文变量
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	//创建存储输入动作变量
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;


	void Move(const  FInputActionValue& InputActionValue);
	//光标追踪
	void CursorTrace();

    IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	
};
