// 关于GAS系统的学习


#include "AbilitySystem/AureAbilitySysTEM_BFL.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AureGameplayTags.h"
#include "AureRPGAbilityTypes.h"
#include "Engine/OverlapResult.h"
#include "Game/AureGameModeBase.h"
#include "HUD/AureHUD.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/APlayerState.h"

UOverlayWidgetController* UAureAbilitySysTEM_BFL::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    FWidgetControllerParams WidgetControllerParams;
	AAureHUD* AureHUD = nullptr;
    if (MakeWidgetControllerParams(WorldContextObject,WidgetControllerParams,AureHUD))
    {
	    return AureHUD->GetOverlayWidgetController(WidgetControllerParams);
    }
	
	return nullptr;
}

UAttributeMenuWidgetController* UAureAbilitySysTEM_BFL::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AAureHUD* AureHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject,WidgetControllerParams,AureHUD))
	{
		return AureHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}
	
	return nullptr;
}

USpellMenuWidgetController* UAureAbilitySysTEM_BFL::GetSpellMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AAureHUD* AureHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject,WidgetControllerParams,AureHUD))
	{
		return AureHUD->GetSpellMenuWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

bool UAureAbilitySysTEM_BFL::MakeWidgetControllerParams(const UObject* WorldContextObject,
	FWidgetControllerParams& WidgetControllerParams, AAureHUD*& OutAureHUD)
{
	//获取到玩家控制器，传入一个世界空间上下文对象，用于得到对应世界中的PC列表，0为本地使用的PC
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		//获取到HUD
		if (AAureHUD* AureHUD = Cast<AAureHUD>(PC->GetHUD()))
		{
			OutAureHUD = AureHUD;//修改指针引用
			AAPlayerState* PS = PC->GetPlayerState<AAPlayerState>();
			//设置参数
			WidgetControllerParams.PlayerController = PC;
			WidgetControllerParams.PlayerState = PS;
			WidgetControllerParams.AbilitySystemComponent= PS->GetAbilitySystemComponent();
			WidgetControllerParams.AttributeSet = PS->GetAttributeSet();
			return true;
		}
	}
	return false;
}

void UAureAbilitySysTEM_BFL::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* AbilitySystemComponent)
{
	AAureGameModeBase* AureGameMode = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AureGameMode==nullptr) 
	{
		return;
	}
	//FPredictionKey PredictionKey = AbilitySystemComponent->GetPredictionKeyForNewAction() ;
	const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();

	const UCharacterClassInfo* CharacterClassInfo = AureGameMode->CharacterClassInfo;

	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

    FGameplayEffectContextHandle PrimaryAttributeContextHandle = AbilitySystemComponent->MakeEffectContext();
	PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributespecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttribute,Level,PrimaryAttributeContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryAttributespecHandle.Data.Get());
	
    FGameplayEffectContextHandle SecondaryAttributeContextHandle = AbilitySystemComponent->MakeEffectContext();
	SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributespecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttribute,Level,SecondaryAttributeContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryAttributespecHandle.Data.Get());

	
    FGameplayEffectContextHandle VitalAttributeContextHandle = AbilitySystemComponent->MakeEffectContext();
	VitalAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributespecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttribute,Level,VitalAttributeContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalAttributespecHandle.Data.Get());
}

void UAureAbilitySysTEM_BFL::GiveStartupAbilities(const UObject* WorldContextObject,
	UAbilitySystemComponent* AbilitySystemComponent,ECharacterClass CharacterClass)
{

	//应用角色拥有的技能
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo==nullptr) return;
    for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
    {
    	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
    	AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
    //获取角色的默认基础数据（职业）
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	//应用角色的职业技能数组
	for (TSubclassOf<UGameplayAbility> AbilityClass : ClassDefaultInfo.StartupAbilities)
    {
	    if (AbilitySystemComponent->GetAvatarActor()->Implements<UCombatInterface>())
	    {
	    	FGameplayAbilitySpec AbilitySpec =
	    		FGameplayAbilitySpec(AbilityClass,ICombatInterface::Execute_GetLevel(AbilitySystemComponent->GetAvatarActor()));
	    	AbilitySystemComponent->GiveAbility(AbilitySpec);//只应用不激活
	    }
    }
}

int32 UAureAbilitySysTEM_BFL::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, int32 Level)
{
	//获取关卡角色配置
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo==nullptr)return 0;
	
	//获取到默认的基础角色数据
	const FCharacterClassDefaultInfo& ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	const float XPReward = ClassDefaultInfo.XPReward.GetValueAtLevel(Level);

	return static_cast<int32>(XPReward);
}

UAbilityInfo* UAureAbilitySysTEM_BFL::GetAbilityInfo(const UObject* WorldContextObject)
{
	//获取到当前关卡的游戏模式实例
	const AAureGameModeBase* AureGameMode = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(AureGameMode == nullptr) return nullptr;
	//返回关卡的角色的技能配置
	return AureGameMode->AbilityInfo;
}

FGameplayEffectContextHandle UAureAbilitySysTEM_BFL::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
    const FAureGameplayTags& GameplayTags = FAureGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceASC->GetAvatarActor();

	//创建GE的上下文句柄
	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	//设置死亡冲击力
	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	//设置攻击击退
	SetKnockbackForceDirection(EffectContextHandle, DamageEffectParams.KnockbackForceDirection);

	//根据句柄和类创建实例
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceASC->MakeOutgoingSpec(
		DamageEffectParams.DamageGameplayEffectClass,
		DamageEffectParams.AbilityLevel, EffectContextHandle);

    //通过标签设置GE使用的配置
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.DeBuff_Chance, DamageEffectParams.DeBuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.DeBuff_Damage, DamageEffectParams.DeBuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.DeBuff_Duration, DamageEffectParams.DeBuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.DeBuff_Frequency, DamageEffectParams.DeBuffFrequency);

	//将GE应用给目标ASC
	DamageEffectParams.TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContextHandle;
}

bool UAureAbilitySysTEM_BFL::IsDeBuffApplied(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext->IsDeBuffApplied();
	}
	return false;
}

float UAureAbilitySysTEM_BFL::GetDeBuffDamage(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext->GetDeBuffDamage();
	}
	return 0.f;
}

float UAureAbilitySysTEM_BFL::GetDeBuffDuration(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext-> GetDeBuffDuration();
	}
	return 0.f;
}

float UAureAbilitySysTEM_BFL::GetDeBuffFrequency(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext-> GetDeBuffFrequency();
	}
	return 0.f;
}

FGameplayTag UAureAbilitySysTEM_BFL::GetDeBuffDamageType(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		if (AureEffectContext->GetDeBuffDamageType().IsValid())
		{
			return *AureEffectContext->GetDeBuffDamageType();
		}
		
	}
	return FGameplayTag();
}

void UAureAbilitySysTEM_BFL::SetDeBuffApplied(FGameplayEffectContextHandle& EffectContext, const bool bInDeBuffApplied)
{
	FAureRPGGameplayEffectContext* AureEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	AureEffectContext->SetDeBuffApplied(bInDeBuffApplied);
}

void UAureAbilitySysTEM_BFL::SetDeBuff(FGameplayEffectContextHandle& EffectContext, FGameplayTag& InDamageType,
	float InDeBuffDamage, float InDeBuffDuration, float InDeBuffFrequency)
{
	FAureRPGGameplayEffectContext* AureEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	//通过标签创建一个共享指针
	const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
	AureEffectContext->SetDeBuffDamageType(DamageType);
	AureEffectContext->SetDeBuffDamage(InDeBuffDamage);
	AureEffectContext->SetDeBuffDuration(InDeBuffDuration);
	AureEffectContext->SetDeBuffFrequency(InDeBuffFrequency);
}

FVector UAureAbilitySysTEM_BFL::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

void UAureAbilitySysTEM_BFL::SetDeathImpulse(FGameplayEffectContextHandle& EffectContext, const FVector& InDeathImpulse)
{
	FAureRPGGameplayEffectContext* AureEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	AureEffectContext->SetDeathImpulse(InDeathImpulse);
}

FVector UAureAbilitySysTEM_BFL::GetKnockbackForceDirection(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureEffectContext->GetKnockbackForceDirection();
	}
	return FVector::ZeroVector;
}

void UAureAbilitySysTEM_BFL::SetKnockbackForceDirection(FGameplayEffectContextHandle& EffectContext,
	const FVector& InKnockbackForceDirection)
{
	FAureRPGGameplayEffectContext* AureEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	AureEffectContext->SetKnockbackForceDirection(InKnockbackForceDirection);
}

TArray<FRotator> UAureAbilitySysTEM_BFL::EvenlySpacedRotators(int32 NumRotators, const FVector& Axis,
	const FVector& Forword, float Speard)
{
	TArray<FRotator> Rotators;
	const FVector LeftOfSpread = Forword.RotateAngleAxis(-Speard / 2, Axis);//获取到最左侧的角度

	if (NumRotators > 1)
	{
		const float DeltaSpread = Speard/(NumRotators-1);//技能分的段数
		for (int32 i = 0; i < NumRotators; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);//获取当前分段的角度
			Rotators.Add(Direction.Rotation());
		}
	}
	else
	{
		//如果只需要一个，则将朝向放入即可
		Rotators.Add(Forword.Rotation());
	}
	return Rotators;
}

TArray<FVector> UAureAbilitySysTEM_BFL::EvenlyRotatedVectors(int32 NumVectors, const FVector& Axis,
	const FVector& Forword, float Speard)
{
	TArray<FVector> Vectors;

	const FVector LeftOfSpread = Forword.RotateAngleAxis(-Speard / 2, Axis);//获取到最左侧的角度
	if (NumVectors > 1)
	{
		const float DeltaSpread = Speard / (NumVectors-1);//技能分的段数
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);//获取当前分段的角度
			Vectors.Add(Direction);
		}
	}
	else
	{
		//如果只需要一个，则将朝向放入即可
		Vectors.Add(Forword);
	}
	return Vectors;
}


UCharacterClassInfo* UAureAbilitySysTEM_BFL::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	//获取当前关卡的游戏模式
 const AAureGameModeBase* AureGameMode = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
 if (AureGameMode == nullptr) return nullptr;
	//返回关卡的角色信息
	return AureGameMode->CharacterClassInfo;
}

bool UAureAbilitySysTEM_BFL::IsBlockedHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureRPGGameplayEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
	{
		return AureRPGGameplayEffectContext->IsBlockedHit();
	}
	return false;
	
}

bool UAureAbilitySysTEM_BFL::IsCriticalHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FAureRPGGameplayEffectContext* AureRPGGameplayEffectContext = static_cast<const FAureRPGGameplayEffectContext*>(EffectContext.Get()))
		{
		return AureRPGGameplayEffectContext->IsCriticalHit();
	}
	return false;
}

void UAureAbilitySysTEM_BFL::SetBlockedHit(FGameplayEffectContextHandle& EffectContext, const bool bInBlockedHit)
{
	FAureRPGGameplayEffectContext* AureRPGGameplayEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	AureRPGGameplayEffectContext->SetBlockedHit(bInBlockedHit);
}

void UAureAbilitySysTEM_BFL::SetCriticalHit(FGameplayEffectContextHandle& EffectContext, const bool bInCriticalHit)
{
	FAureRPGGameplayEffectContext* AureRPGGameplayEffectContext = static_cast<FAureRPGGameplayEffectContext*>(EffectContext.Get());
	AureRPGGameplayEffectContext->SetCriticalHit(bInCriticalHit);
}

void UAureAbilitySysTEM_BFL::GetLivePlayerWithRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
    FCollisionQueryParams SpereParams;//创建一个碰撞查询配置
	SpereParams.AddIgnoredActors(ActorsToIgnore);//忽略Actor

	//创建存储检索到的与碰撞体产生碰撞的Actor的数组
	TArray<FOverlapResult> Overlaps;
	//获取当前所处的场景，如果获取失败，将打印并返回Null
    if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        //获取所有与此球踢碰撞的动态对象
    	World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
		FCollisionShape::MakeSphere(Radius), SpereParams);
        //遍历所有获取到的Actor
    	for (FOverlapResult& Overlap : Overlaps)
    	{
    		//判断当前Actor是否具有CombatInterface组件
    		const bool ImplementsCombatInterface = Overlap.GetActor()->Implements<UCombatInterface>();
            
		    if (ImplementsCombatInterface && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
		    {
		    	//将获取到的Actor添加到输出数组中
			    OutOverlappingActors.AddUnique(Overlap.GetActor());
		    }
    	}
	    
    }
}

bool UAureAbilitySysTEM_BFL::IsEnemy(const AActor* ActorA, const AActor* ActorB)
{
	if (ActorA->ActorHasTag("Player"))
	{
		return !ActorB->ActorHasTag("Player");
	}
	if (ActorA->ActorHasTag("Enemy"))
	{
		return !ActorB->ActorHasTag("Enemy");
	}

	return false;
}


