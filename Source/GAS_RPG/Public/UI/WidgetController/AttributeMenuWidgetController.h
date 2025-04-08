// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AureWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */

class UAttributeInfo_DataAsset;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttibuteInfoSignature, const FAureAttributeInfo&, AttributeInfo);


UCLASS(BlueprintType, Blueprintable)
class GAS_RPG_API UAttributeMenuWidgetController : public UAureWidgetController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual  void BroadcastInitialValues() override;
	virtual  void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FAttibuteInfoSignature AttributeInfoDelegate;

	//属性点变化的监听委托
	UPROPERTY(BlueprintAssignable,Category="Widget Controller")
	FOnPlayStateChangedSignature AttributePointsChangedDelegate;

	//升级属性
	UFUNCTION(BlueprintCallable,Category="GAS|Attributes")
	void UpgradeAttribute(const FGameplayTag& AttributeTag);
	
private:
	UPROPERTY(EditDefaultsOnly,Category="Widget Controller")
	TObjectPtr<UAttributeInfo_DataAsset> AttributeInfo;

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute)const;
	
};
