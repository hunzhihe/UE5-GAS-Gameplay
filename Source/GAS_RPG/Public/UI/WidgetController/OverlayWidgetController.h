// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
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

protected:
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	// void HealthChanged(const FOnAttributeChangeData& Data) const;
	//void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	//void ManaChanged(const FOnAttributeChangeData& Data) const;
	//void MaxManaChanged(const FOnAttributeChangeData& Data) const;


	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag) const
	{
	 T* Row= DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
		 return Row;
	}
};
