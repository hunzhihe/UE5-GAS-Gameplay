// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"


#include "AureWidgetController.generated.h"


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
protected:
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,  Category = "AureWidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
