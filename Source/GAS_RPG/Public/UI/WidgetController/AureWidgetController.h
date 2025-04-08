// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Date/AbilityInfo.h"


#include "AureWidgetController.generated.h"


class UAureAttributeSet;
class UAureAbilitySystemComponentBase;
class AAPlayerState;
class AAurePlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayStateChangedSignature, int32, newValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignatuire,const FAureAbilityInfo,Info);
/**
 * 
 */
USTRUCT(BlueprintType)

struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PlayerController,UAttributeSet* AttributeSet,APlayerState* PlayerState,UAbilitySystemComponent* AbilitySystemComponent)
	: PlayerController(PlayerController),AttributeSet(AttributeSet),PlayerState(PlayerState),AbilitySystemComponent(AbilitySystemComponent){}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController =nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState  = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent =nullptr;


	
};
//控件类
UCLASS()
class GAS_RPG_API UAureWidgetController : public UObject
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);

	virtual  void BroadcastInitialValues();

	virtual  void BindCallbacksToDependencies();

	
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FAbilityInfoSignatuire OnAbilityInfoDelegate;



	//广播技能信息
	void BroadcastAbilityInfo();

	//监听技能装配后的处理
	void OnAbilityEquipped(const FGameplayTag& AbilityTag,const FGameplayTag& StatusTag,const FGameplayTag& SlotTag,const FGameplayTag& PreviousSlot);
protected:
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<AAurePlayerController> AurePlayerController;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<AAPlayerState> AurePlayerState;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAureAbilitySystemComponentBase> AureAbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAureAttributeSet> AureAttributeSet;
	//技能的表格数据
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Date")
	TObjectPtr<UAbilityInfo> AbilityInfo;


	AAurePlayerController* GetAurePlayerController();
	AAPlayerState* GetAurePlayerState();
	UAureAbilitySystemComponentBase* GetAureAbilitySystemComponent();
	UAureAttributeSet* GetAureAttributeSet();
};
