// 关于GAS系统的学习


#include "Character/AureEnemy.h"

#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS_RPG/GAS_RPG.h"

AAureEnemy::AAureEnemy()
{
   GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAureAbilitySystemComponentBase>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);
   AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	
	AttributeSet = CreateDefaultSubobject<UAureAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AAureEnemy::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAureEnemy::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAureEnemy::GetLevel()
{
	return Level;
}

void AAureEnemy::HitReactTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

//死亡函数
void AAureEnemy::Die()
{
	//死亡设置清除时间
	SetLifeSpan(lifeSpan);
	Super::Die();
}

void AAureEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
	GetCharacterMovement()->MaxWalkSpeed =  BaseWalkSpeed;
	//初始化ASC
    InitAbilityActorInfo();

	UAureAbilitySysTEM_BFL::GiveStartupAbilities(this,AbilitySystemComponent);

	
	//将敌人基类作为控制器绑定给用户控件
	if (UAureUserWidget* UserWidget =Cast<UAureUserWidget>(HealthBar->GetUserWidgetObject()) )
	{
		UserWidget->SetWidgetController(this);
	}

	if (const UAureAttributeSet* AureAS = Cast<UAureAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAS->GetShengMingZhiAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnShengMingzhiChanged.Broadcast(Data.NewValue);
		}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AureAS->GetMaxShengMingZhiAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHpChanged.Broadcast(Data.NewValue);
		}
		);
        AbilitySystemComponent->RegisterGameplayTagEvent(FAureGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAureEnemy::HitReactTagChanged);
		
		OnShengMingzhiChanged.Broadcast(AureAS->GetShengMingZhi());
		OnMaxHpChanged.Broadcast(AureAS->GetMaxShengMingZhi());
	}
}

void AAureEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAureAbilitySystemComponentBase>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
	
}

void AAureEnemy::InitializeDefaultAttributes() const
{
	//Super::InitializeDefaultAttributes();
	UAureAbilitySysTEM_BFL::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
