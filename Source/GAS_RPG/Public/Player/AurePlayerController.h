// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
//#include "AbilitySystemComponent.h"
#include "InputMappingContext.h"
//#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "GameFramework/PlayerController.h"
#include "Input/DA_Input.h"
#include "UI/Widgets/DamageTextComponent.h"
#include "AurePlayerController.generated.h"


class USplineComponent;
/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct  FInputActionValue;
class IEnemyInterface;
class UAureAbilitySystemComponentBase;
UCLASS()
class GAS_RPG_API AAurePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAurePlayerController();
	virtual  void PlayerTick(float DeltaTime) override;
    UFUNCTION(Client,Reliable)
	void ShowDamagedNumber(float Damage,ACharacter*TargetCharacter);
	
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

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UAureDA_Input> InputConfig;

	//攻击动作变量
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAttackAction;

	UPROPERTY()
	TObjectPtr<UAureAbilitySystemComponentBase> AureBaseASC;

	UAureAbilitySystemComponentBase * GetAureBaseASC();
	
	void Move(const  FInputActionValue& InputActionValue);

	void AbilityInputTagPressed( FGameplayTag InputTag);
	void AbilityInputTagReleased( FGameplayTag InputTag);
	void AbilityInputTagHold( FGameplayTag InputTag);
	bool bShiftKeyDown = false;
	void ShiftPressed() {  bShiftKeyDown = true; };
	void ShiftReleased() {  bShiftKeyDown = false; };
	
	//鼠标位置追踪
	void CursorTrace();
	//上一帧拾取的接口指针
    IEnemyInterface* LastActor;
	//当前帧拾取的接口指针
	IEnemyInterface* ThisActor;

    //储存鼠标所点击的位置
	FVector CachedDestination = FVector::ZeroVector;
	float holdTime= 0.f;//按压时间
	bool bHasAutoRuning =false;//是否自动移动
	bool bTargeting = false;//鼠标是否选中敌人
	
	FHitResult Hit ;
	//FHitResult CursorHit;

	UPROPERTY(EditDefaultsOnly)
	float ShortPresshold = 0.5f;//定义鼠标悬停多长时间算点击事件

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptRadius = 50.f;//自动移动半径,小于时关闭寻路

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USplineComponent> Spline;//路线样条线

	void AutoRun();
	
    UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
};       
