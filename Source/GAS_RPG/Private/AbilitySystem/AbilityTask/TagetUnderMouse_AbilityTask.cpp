// 关于GAS系统的学习


#include "AbilitySystem/AbilityTask/TagetUnderMouse_AbilityTask.h"

#include <iomanip>

#include "AbilitySystemComponent.h"

UTagetUnderMouse_AbilityTask* UTagetUnderMouse_AbilityTask::CreateTagetDataUnderMouse_AbilityTask(
	UGameplayAbility* OwningAbility)
{
	UTagetUnderMouse_AbilityTask* MyObj = NewAbilityTask<UTagetUnderMouse_AbilityTask>(OwningAbility);
	return MyObj;
	
}

void UTagetUnderMouse_AbilityTask::Activate()
{
	// 判断是否本地(客户)控制
 const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		//本地控制
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTagetUnderMouse_AbilityTask::OnTargetDataReplicatedCallback);
        //判断在服务器端，是否已经处理了数据
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTagetUnderMouse_AbilityTask::SendMouseCursorData() const
{
	//预测窗口
     FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get(),true);

	//获取鼠标拾取结果
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorResult;

		
		PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,CursorResult);
	
	//需要上传到服务器的数据
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit(CursorResult);

	//数据句柄
	FGameplayAbilityTargetDataHandle  DataHandle;
	DataHandle.Add(Data);
	//调用函数上传数据 
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
        GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
		);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTagetUnderMouse_AbilityTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag) const
{
   //通知客户端，服务器端已经接收并处理了从客户端复制的目标数据（将服务器的TargetData应用到客户端，并清除缓存）
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	//判断服务器端是否通过验证
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
