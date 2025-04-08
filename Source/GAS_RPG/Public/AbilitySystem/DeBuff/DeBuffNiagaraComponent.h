// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "DeBuffNiagaraComponent.generated.h"


/**
 * 
 */
UCLASS()
class GAS_RPG_API UDeBuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	UDeBuffNiagaraComponent();

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DebuffTag; //用来标识例子系统的标签
protected:
	virtual void BeginPlay() override;
	void DeBuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);//当前的负面标签回调

	UFUNCTION()
	void OnOwnerDeath(AActor* DeadActor);//在角色死亡时的回调
	
};
