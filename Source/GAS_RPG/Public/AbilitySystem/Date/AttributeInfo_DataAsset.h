// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo_DataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAureAttributeInfo
{
	GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
};
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAttributeInfo_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	FAureAttributeInfo FindAttributeInfoForTag(const FGameplayTag& Tag,bool bLogNotFound = false)const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAureAttributeInfo> AttributeInformation;


	
};
