// 关于GAS系统的学习


#include "AbilitySystem/AureAbilitySysTEM_BFL.h"

#include "Game/AureGameModeBase.h"
#include "HUD/AureHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/APlayerState.h"

UOverlayWidgetController* UAureAbilitySysTEM_BFL::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAureHUD* AureHUD = Cast<AAureHUD>(PC->GetHUD()))
		{
			AAPlayerState* PS = PC->GetPlayerState<AAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,AS,PS,ASC);
			return  AureHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAureAbilitySysTEM_BFL::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAureHUD* AureHUD = Cast<AAureHUD>(PC->GetHUD()))
		{
			AAPlayerState* PS = PC->GetPlayerState<AAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,AS,PS,ASC);
			return  AureHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UAureAbilitySysTEM_BFL::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* AbilitySystemComponent)
{
	AAureGameModeBase* AureGameMode = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AureGameMode==nullptr) 
	{
		return;
	}

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
	UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAureGameModeBase* AureGameMode = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AureGameMode == nullptr) return;
	
	//const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
	UCharacterClassInfo* CharacterClassInfo = AureGameMode->CharacterClassInfo;
    for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
    {

    	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
    	AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
	
}
