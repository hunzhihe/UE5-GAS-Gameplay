// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/Date/AbilityInfo.h"
#include "UI/WidgetController/AureWidgetController.h"
#include "UI/Widgets/AureUserWidget.h"
#include "OverlayWidgetController.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,newHealth);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,newMaxHealth);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,newMana);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,newMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature,float,newValue);



USTRUCT(BlueprintType)

struct  FUIWidgetRow : public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAureUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Image = nullptr;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class GAS_RPG_API UOverlayWidgetController : public UAureWidgetController
{
	GENERATED_BODY()
public:
	//广播初始值以及将回调绑定到依赖项
	virtual  void BroadcastInitialValues() override;
	virtual  void BindCallbacksToDependencies() override;
	
    UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FMessageWidgetRowSignature OnMessageWidgetRowDelegate;

	

	//经验条百分比变动回调
	UPROPERTY(BlueprintAssignable,Category="GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangeDelegate;
    //等级变动回调
    UPROPERTY(BlueprintAssignable,Category="GAS|Level")
	FOnPlayStateChangedSignature OnPlayerLevelChangedDelegate;
	
protected:
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;



	//经验变动后的回调
	void OnXPChanged(int32 NewXP);

	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag) const
	{
	 T* Row= DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
		 return Row;
	}
};
