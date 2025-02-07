// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TagetUnderMouse_AbilityTask.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetUnderMouse, const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class GAS_RPG_API UTagetUnderMouse_AbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TagetDataUnderMouse",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTagetUnderMouse_AbilityTask* CreateTagetDataUnderMouse_AbilityTask(UGameplayAbility* OwningAbility);

    //有效数据，可通过蓝图分配
    UPROPERTY(BlueprintAssignable)
	FOnTargetUnderMouse ValidData;

private:
	virtual void Activate() override;

	//客户端向服务端提交数据
    void SendMouseCursorData() const;

    //当数据提交到服务器端后的委托回调
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const;
};
