// 关于GAS系统的学习


#include "Actor/AureEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AureAttributeSet.h"

// Sets default values
AAureEffectActor::AAureEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	
	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AAureEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherCom, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//为展示属性改变的示例而实现的错误示范，以后会利用游戏效果来替代掉
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
	const  UAureAttributeSet* AureAttributeSet = Cast<UAureAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAureAttributeSet::StaticClass()));
		UAureAttributeSet* NutableAureAttributeSet = const_cast<UAureAttributeSet*>(AureAttributeSet);
		NutableAureAttributeSet->SetShengMingZhi(AureAttributeSet->GetShengMingZhi()+25.f);
		Destroy();
	};
	
}

void AAureEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void AAureEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAureEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAureEffectActor::EndOverlap);
}



