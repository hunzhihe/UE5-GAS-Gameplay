// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
//角色职业 法师，战士，游侠，
    Elementalist,
	Warrior,
	Ranger,
	
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttribute;
};

UCLASS()
class GAS_RPG_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttribute;

	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttribute;

	//用于设置创建敌人所拥有的初始技能
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	//通过上面的枚举类获取对应的初始化类
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass Class) const;
};
