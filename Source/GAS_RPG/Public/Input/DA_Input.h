// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_Input.generated.h"

USTRUCT(BlueprintType)
struct FAureInputAction
{
	GENERATED_BODY()
	
    UPROPERTY(EditDefaultsOnly)
    const class UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTags = FGameplayTag();

	
	
};
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureDA_Input : public UDataAsset
{
	GENERATED_BODY()
public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAureInputAction> AbilityInputActions;
};
