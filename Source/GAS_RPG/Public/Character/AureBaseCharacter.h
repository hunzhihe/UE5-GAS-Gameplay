// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AureBaseCharacter.generated.h"

UCLASS()
class GAS_RPG_API AAureBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAureBaseCharacter();

protected:
	
	virtual void BeginPlay() override; 

	//指针变量：武器组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
