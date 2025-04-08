// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Character/AureBaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "AureCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureCharacter : public AAureBaseCharacter,public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAureCharacter();
    /* IPlayerInterface战斗接口*/
    virtual  void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePoints_Implementation(int32 Level) const override;
	virtual int32 GetSkillPoints_Implementation(int32 Level) const override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSkillPoints_Implementation(int32 InSkillPoints) override;
	virtual void AddToPlayerLevel_Implementation(int32 InLevel) override;
	virtual int32 GetAttributesPoints_Implementation() const override;
	/* IPlayerInterface战斗接口*/
	
	virtual  void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* ICombatInterface战斗接口*/
	virtual  int32 GetLevel_Implementation() override;
	/* ICombatInterface战斗接口*/

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;
private:

	UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> TopDownCameraComponent;
    UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoon;

	
	virtual  void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast,Reliable)
	void MulticastLevelUpParticles() const;
	
};
