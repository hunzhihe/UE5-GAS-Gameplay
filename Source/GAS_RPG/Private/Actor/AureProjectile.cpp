// 关于GAS系统的学习


#include "Actor/AureProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GAS_RPG/GAS_RPG.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAureProjectile::AAureProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	//初始化碰撞体
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionProfileName(TEXT("Projectile"));
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//碰撞设置只用来检测，不响应碰撞
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);//设置其忽略所有碰撞检测
    Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);// 设置其与世界动态物体产生重叠事件
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);// 设置其与世界静态物体产生重叠事件
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);// 设置其与Pawn类角色产生重叠事件
    //初始化发射组件
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;


}

// Called when the game starts or when spawned
void AAureProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	//绑定碰撞检测回调
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAureProjectile::OnSphereOverlap);

	//添加一个跟随音效
	LoopSoundComponent = UGameplayStatics::SpawnSoundAttached(FlightLoopSound, RootComponent);
}

void AAureProjectile::Destroyed()
{
	//如果对火球没有权威性控制权，并且现在还没有触发碰撞体的重叠事件，那就在销毁时播放击中特效
	if (!bHasHit && !HasAuthority())
	{
		PlayEffects();
	}
	Super::Destroyed();
}

void AAureProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayEffects();
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHasHit= true;
	}
	
}

void AAureProjectile::PlayEffects() const
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());

	LoopSoundComponent->Stop();
}



