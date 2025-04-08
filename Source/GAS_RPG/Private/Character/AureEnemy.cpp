// 关于GAS系统的学习


#include "Character/AureEnemy.h"

#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "AbilitySystem/AureAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	//血条组件
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

    bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
	
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

AActor* AAureEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}



void AAureEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}


int32 AAureEnemy::GetLevel_Implementation()
{
	return Level;
}

void AAureEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//该设置只在服务器端生效
	if (!HasAuthority())return;
    //AI控制器在服务器运行，因此要在possessedby中获取服务器返回
	AureAIController = Cast<AAureAIController>(NewController);
    //初始化行为树上的黑板
	AureAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

	AureAIController->RunBehaviorTree(BehaviorTree);


	AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	// if (CharacterClass == ECharacterClass::Warrior)
	// {
	// 	AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),false);
	// }
	// else 
	// {
	// 	AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),true);
	// }
	AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),CharacterClass != ECharacterClass::Warrior);
	
}

void AAureEnemy::HitReactTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;

	//设置黑板键的值
	if (AureAIController && AureAIController->GetBlackboardComponent())
	{
		AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

//死亡函数
void AAureEnemy::Die(const FVector& DeathImpulse)
{
	//死亡设置清除时间
	SetLifeSpan(lifeSpan);
	if (AureAIController && AureAIController->GetBlackboardComponent())
	{
		AureAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), false);
	}
	Super::Die(DeathImpulse);
}

void AAureEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
	GetCharacterMovement()->MaxWalkSpeed =  BaseWalkSpeed;
	//初始化ASC
    InitAbilityActorInfo();

	if (HasAuthority())
	{
		UAureAbilitySysTEM_BFL::GiveStartupAbilities(this,AbilitySystemComponent,CharacterClass);
	}
	//UAureAbilitySysTEM_BFL::GiveStartupAbilities(this,AbilitySystemComponent);

	
	//将敌人基类作为控制器绑定给用户控件
	if (UAureUserWidget* UserWidget =Cast<UAureUserWidget>(HealthBar->GetUserWidgetObject()) )
	{
		UserWidget->SetWidgetController(this);
	}

	if (const UAureAttributeSet* AureAS = Cast<UAureAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AureAS->GetShengMingZhiAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnShengMingzhiChanged.Broadcast(Data.NewValue);
		}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AureAS->GetMaxShengMingZhiAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
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

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}

	OnAscRegistered.Broadcast(AbilitySystemComponent);
	
}

void AAureEnemy::InitializeDefaultAttributes() const
{
	//Super::InitializeDefaultAttributes();
	UAureAbilitySysTEM_BFL::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}


