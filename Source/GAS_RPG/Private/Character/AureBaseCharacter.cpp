// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AureBaseCharacter.h"

// Sets default values
AAureBaseCharacter::AAureBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//武器组件，创建默认子对象
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//设置附件，将其附加到网格体上并连接到插槽
	Weapon->SetupAttachment(GetMesh(),FName(TEXT("WeaponHandSocket")));
	//设置碰撞：无
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAureBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AAureBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AAureBaseCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

// Called to bind functionality to input
//void AAureBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);

//}

