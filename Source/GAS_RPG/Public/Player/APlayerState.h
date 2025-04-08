// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Date/LevelUpInfo.h"
#include "GameFramework/PlayerState.h"
#include "APlayerState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayStateChanged,int32/*状态值，当其中一个状态发生变化时，将向绑定到我们委托的任何人广播*/);

class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class GAS_RPG_API AAPlayerState : public APlayerState ,public IAbilitySystemInterface 
{
	GENERATED_BODY()

public: AAPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet()const {return AttributeSet;}


	//经验值变动委托
	FOnPlayStateChanged OnXPChangedDelegate;
	//等级变动委托
	FOnPlayStateChanged OnLevelChangedDelegate;
    //属性点变动委托
	FOnPlayStateChanged OnAttributePointsChangedDelegate;
	//技能点变动委托
	FOnPlayStateChanged OnSpellPointsChangedDelegate;
	

	//-----等级------
	// 获取等级
	FORCEINLINE int32 GetPlayerLevel()const { return Level;}
	//增加等级
	void AddToLevel(int32 InLevel);
	//设置当前等级
	void SetLevel(int32 InLevel);

	//-----经验值------
	//获取当前经验值
	FORCEINLINE int32 GetXP()const { return XP;}
	//增加经验值
	void AddToXP(int32 InXP);
	//设置当前经验值
	void SetXP(int32 InXP);

	//-----属性点------
	FORCEINLINE int32 GetAttributePoints()const { return AttributePoints;}
	void AddToAttributePoints(int32 InAttributePoints);
	void SetAttributePoints(int32 InAttributePoints);

	//-----技能点------
	FORCEINLINE int32 GetSkillPoints()const { return SpellPoints;}
	void AddToSkillPoints(int32 InSkillPoints);
	void SetSkillPoints(int32 InSkillPoints);

    //设置相关升级数据
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere,  ReplicatedUsing = OnRep_Level, Category = "Level" )
    int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP, Category = "XP" )
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints, Category = "AttributePoints")
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints, Category = "AttributePoints")
	int32 SpellPoints = 1;

	/*服务端到客户端的同步函数*/
	UFUNCTION()
	void OnRep_Level(int32 OldLevel) const;
	UFUNCTION()
	void OnRep_XP(int32 OldXP) const;
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints) const;
	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints) const;
};
