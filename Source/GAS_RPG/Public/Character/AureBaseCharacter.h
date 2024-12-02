// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AbilitySystemInterface.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "AureBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class GAS_RPG_API AAureBaseCharacter : public ACharacter ,public IAbilitySystemInterface 
{
	GENERATED_BODY()

public:
	
	AAureBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet()const {return AttributeSet;}
protected:
	
	virtual void BeginPlay() override; 
	
	//指针变量：武器组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
