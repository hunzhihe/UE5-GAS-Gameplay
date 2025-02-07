// 关于GAS系统的学习


#include "AbilitySystem/AureAbilitySystemComponentBase.h"

#include "AureGameplayTags.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"

void UAureAbilitySystemComponentBase::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAureAbilitySystemComponentBase::ClientEffectApplied);

	//const FAureGameplayTags& GameplayTags = FAureGameplayTags::Get();
	//GameplayTags.Attribute_Secondary_HuJia
	//GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attribute_Secondary_HuJia.ToString()));
}

void UAureAbilitySystemComponentBase::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
	{
        FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
        if (const UAureGameplayAbility* AureAbility = Cast<UAureGameplayAbility>(AbilitySpec.Ability))
        {
        	AbilitySpec.GetDynamicSpecSourceTags().AddTag(AureAbility->StartupInputTag);
        	//激活能力但不应用
            GiveAbility(AbilitySpec);
        }

		//激活并应用一次
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}

	 
}
// void UAureAbilitySystemComponentBase::AbilityInputTagPressed(FGameplayTag InputTag)
// {
// 	if(InputTag.IsValid())return;
// 	for(FGameplayAbilitySpec& Ability:GetActivatableAbilities())
// 	{
// 		if(Ability.GetDynamicSpecSourceTags().HasTagExact(InputTag))
// 		{
// 			AbilitySpecInputPressed(Ability);
// 			if (!Ability.IsActive())
// 			{
// 				TryActivateAbility(Ability.Handle);
// 			}
// 		}
// 	}
// }
void UAureAbilitySystemComponentBase::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())return;
	for(FGameplayAbilitySpec& Ability:GetActivatableAbilities())
	{
		if(Ability.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Ability);
			if (!Ability.IsActive())
			{
				TryActivateAbility(Ability.Handle);
			}
		}
	}
}
void UAureAbilitySystemComponentBase::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())return;
	for(FGameplayAbilitySpec& Ability:GetActivatableAbilities())
	{
		if(Ability.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Ability);
		}
	}
}
void UAureAbilitySystemComponentBase::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                    const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
}
