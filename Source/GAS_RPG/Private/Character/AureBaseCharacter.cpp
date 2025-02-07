// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AureBaseCharacter.h"
//#include ""

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "GAS_RPG/GAS_RPG.h"
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

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAureBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AAureBaseCharacter::GetHitReactMontage_Implementation()
{
	
	return HitReactMontage;
}

// Called when the game starts or when spawned
void AAureBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



void AAureBaseCharacter::Die()
{
	//将武器从角色身上分离
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
	
    
}
void AAureBaseCharacter::UpdateDissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		//创建一个动态材质实例
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);

		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		//创建一个动态材质实例
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

void AAureBaseCharacter::MulticastHandleDeath_Implementation()
{
	//开启武器物理效果
	if (Weapon)
	{
		//开启角色死亡，武器掉落的物理效果
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

	//开启角色死亡物理效果
	GetMesh()->SetSimulatePhysics(true);//开启模拟物理效果
	GetMesh()->SetEnableGravity(true);//开启重力效果
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);//开启物理碰撞通道
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);//开启角色与静态物体发生碰撞时，进行物理碰撞


	//关闭角色死亡物理效果
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UpdateDissolve();
	//GetCapsuleComponent()->OnComponentOverlap.AddDynamic(this, &AAureBaseCharacter::OnOverlap);
}

FVector AAureBaseCharacter::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
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
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
	
}

void AAureBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.0);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.0);
	ApplyEffectToSelf(DefaultVitalAttributes,1.0);
}

void AAureBaseCharacter::InitializeAbilities()
{
	//服务端进行
	UAureAbilitySystemComponentBase* AureASC = Cast<UAureAbilitySystemComponentBase>(GetAbilitySystemComponent());
	if (!HasAuthority())return;

	AureASC->AddCharacterAbilities(Abilities);
}


