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

UCLASS()
class GAS_RPG_API AAurePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAurePlayerController();
	//创建储存输入映射上下文变量
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
protected:
	virtual  void BeginPlay() override;
};
