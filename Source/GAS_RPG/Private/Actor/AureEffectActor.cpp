// 关于GAS系统的学习


#include "Actor/AureEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "AbilitySystem/AureAttributeSet.h"

// Sets default values
AAureEffectActor::AAureEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// SetRootComponent(Mesh);
	//
	//
	// Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	// Sphere->SetupAttachment(GetRootComponent());

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// void AAureEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherCom, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
	//为展示属性改变的示例而实现的错误示范，以后会利用游戏效果来替代掉
	// if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	// {
	// const  UAureAttributeSet* AureAttributeSet = Cast<UAureAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAureAttributeSet::StaticClass()));
	// 	UAureAttributeSet* NutableAureAttributeSet = const_cast<UAureAttributeSet*>(AureAttributeSet);
	// 	
	// 	NutableAureAttributeSet->SetShengMingZhi(AureAttributeSet->GetShengMingZhi()+25.f);
	// 	NutableAureAttributeSet->SetMona(AureAttributeSet->GetMona()-25.f);
	// 	Destroy();
	// };
	
//}

// void AAureEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// }

// Called when the game starts or when spawned
void AAureEffectActor::BeginPlay()
{
	Super::BeginPlay();
	// Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAureEffectActor::OnOverlap);
	// Sphere->OnComponentEndOverlap.AddDynamic(this,&AAureEffectActor::EndOverlap);
}

void AAureEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//调用Actor的ASC的其中一种方法，条件是必须要实现接口，当然也可使用虚幻自带的蓝图函数库
 //    IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);
	// if (ASCInterface)
	// {
	// 	ASCInterface->GetAbilitySystemComponent();
	// }
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    if (TargetASC==nullptr)return;

	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle TargetAscContextHandle= TargetASC->MakeEffectContext();
	TargetAscContextHandle.AddSourceObject(this);
	 FGameplayEffectSpecHandle TargetAscSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.0f,TargetAscContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*TargetAscSpecHandle.Data.Get());

	//判断游戏效果持续时间策略是否为永久
	const bool bIsInfinite =    TargetAscSpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovedPolicy == EEffectRemovedPolicy::RemoveOnOverlay )
	{
		ActiveGameplayEffectsHandle.Add(ActiveEffectHandle,TargetASC);
	};
}

void AAureEffectActor::OnOverlay(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlay)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlay)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlay)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAureEffectActor::OnEndOverlay(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlay)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlay)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlay)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if(InfiniteEffectRemovedPolicy == EEffectRemovedPolicy::RemoveOnOverlay)
	{
		UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
        TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle,UAbilitySystemComponent*> HandlePair : ActiveGameplayEffectsHandle)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveGameplayEffectsHandle.FindAndRemoveChecked(Handle);
		}
	}
}



