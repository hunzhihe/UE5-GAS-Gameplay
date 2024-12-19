// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AureBaseCharacter.h"
//#include ""

#include "AbilitySystemComponent.h"
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

void AAureBaseCharacter::InitAbilityActorInfo()
{
}

void AAureBaseCharacter::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const
{
	check(AbilitySystemComponent);
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle =  GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}

void AAureBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.0);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.0);
}


