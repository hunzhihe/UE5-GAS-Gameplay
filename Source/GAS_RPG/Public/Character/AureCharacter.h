// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Character/AureBaseCharacter.h"
#include "AureCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAureCharacter : public AAureBaseCharacter
{
	GENERATED_BODY()

public:
	AAureCharacter();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Aure Camera",meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Aure Camera",meta=(AllowPrivateAccess="true"))
	class UCameraComponent* AureCamera;
};
