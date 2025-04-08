// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AureBaseCharacter.h"
//#include ""

#include "AbilitySystemComponent.h"
#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/DeBuff/DeBuffNiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS_RPG/GAS_RPG.h"
#include "Kismet/GameplayStatics.h"
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

	//初始化火焰负面效果组件
	BurnDeBuffNiagaraComponent = CreateDefaultSubobject<UDeBuffNiagaraComponent>("BurnDeBuffNiagaraComponent");
	BurnDeBuffNiagaraComponent->SetupAttachment(GetRootComponent());
	BurnDeBuffNiagaraComponent->DebuffTag = FAureGameplayTags::Get().DeBuff_Burn;//设置标签的负面标题
}

UAbilitySystemComponent* AAureBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AAureBaseCharacter::GetHitReactMontage_Implementation()
{
	
	return HitReactMontage;
}

FVector AAureBaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) const
{
	const FAureGameplayTags& GameplayTags = FAureGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return  Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	return FVector();
}

// FVector AAureBaseCharacter::GetCombatSocketLocation_Implementation(const FTaggedMontage TaggedMontage) const
// {
// 	if (TaggedMontage.MontageTag.MatchesTagExact(FAureGameplayTags::Get().Montage_Attack_Weapon))
// 	{
// 		return  Weapon->GetSocketLocation(TaggedMontage.AttackSocket);
// 	}
// 	else
// 	{
// 		return GetMesh()->GetSocketLocation(TaggedMontage.AttackSocket);
// 	}
// }


// Called when the game starts or when spawned
void AAureBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



void AAureBaseCharacter::Die(const FVector& DeathImpulse)
{
	//将武器从角色身上分离
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath(DeathImpulse);
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



void AAureBaseCharacter::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(),GetActorRotation());
	//开启武器物理效果
	if (Weapon)
	{
		//开启角色死亡，武器掉落的物理效果
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		//添加一个冲量,大小为百分之一，第二个参数是接收冲击的骨骼，默认NAME_None就是应用根骨骼
		Weapon->AddImpulse(DeathImpulse*0.01f,NAME_None,true);
	}

	//开启角色死亡物理效果
	GetMesh()->SetSimulatePhysics(true);//开启模拟物理效果
	GetMesh()->SetEnableGravity(true);//开启重力效果
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);//开启物理碰撞通道
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);//开启角色与静态物体发生碰撞时，进行物理碰撞
	//添加一个冲量,大小不变，第二个参数是接收冲击的骨骼，默认NAME_None就是应用根骨骼
    GetMesh()->AddImpulse(DeathImpulse,NAME_None,true);

	//关闭角色死亡物理效果
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//开始溶解动画
	UpdateDissolve();
	//GetCapsuleComponent()->OnComponentOverlap.AddDynamic(this, &AAureBaseCharacter::OnOverlap);
	//设置死亡
	bDead = true;

	//触发死亡委托
	OnDeath.Broadcast(this);
}



bool AAureBaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AAureBaseCharacter* AAureBaseCharacter::GetAvatar_Implementation() 
{
	return this;
}

TArray<FTaggedMontage> AAureBaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AAureBaseCharacter::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AAureBaseCharacter::GetTaggedMontageByTag_Implementation(const FGameplayTag& TagMontages)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == TagMontages)
		{
           return TaggedMontage; 
		}
	}
	return FTaggedMontage();
}

int32 AAureBaseCharacter::GetMinionsCount_Implementation()
{
	return MinionsCount;
}

void AAureBaseCharacter::IncrementMinionsCount_Implementation(const int32 Amount)
{
	MinionsCount+=Amount;
}

ECharacterClass AAureBaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

FOnASCRegistered& AAureBaseCharacter::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

FOnDeath& AAureBaseCharacter::GetOnDeathDelegate()
{
	return OnDeath;
}

void AAureBaseCharacter::InitAbilityActorInfo()
{
}

void AAureBaseCharacter::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const
{
	check(AbilitySystemComponent);
	check(GameplayEffectClass);
	FPredictionKey PredictionKey = AbilitySystemComponent->GetPredictionKeyForNewAction() ;
	FGameplayEffectContextHandle EffectContextHandle =  GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent(),PredictionKey);
	
}

void AAureBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.0);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.0);
	ApplyEffectToSelf(DefaultVitalAttributes,1.0);
}

void AAureBaseCharacter::InitializeAbilities() const
{
	//服务端进行
	UAureAbilitySystemComponentBase* AureASC = Cast<UAureAbilitySystemComponentBase>(GetAbilitySystemComponent());
	if (!HasAuthority())return;//查询是否拥有网络权限，应用技能需要添加给服务器

	AureASC->AddCharacterAbilities(Abilities);
	AureASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}



