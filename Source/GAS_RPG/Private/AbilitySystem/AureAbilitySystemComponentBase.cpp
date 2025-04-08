// 关于GAS系统的学习


#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "UI/WidgetController/AureWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AureGameplayTags.h"
#include "AbilitySystem/AureAbilitySysTEM_BFL.h"
#include "AbilitySystem/Abilitis/AureGameplayAbility.h"
#include "AbilitySystem/Date/AbilityInfo.h"
#include "GAS_RPG/AureLogChannels.h"
#include "Interaction/PlayerInterface.h"


void UAureAbilitySystemComponentBase::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAureAbilitySystemComponentBase::ClientEffectApplied);

	//const FAureGameplayTags& GameplayTags = FAureGameplayTags::Get();
	//GameplayTags.Attribute_Secondary_HuJia
	//GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attribute_Secondary_HuJia.ToString()));
}

void UAureAbilitySystemComponentBase::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		AbilityGivenDelegate.Broadcast();
	}
}

void UAureAbilitySystemComponentBase::ServerEquipAbility_Implementation(const FGameplayTag& AbilityTag,const FGameplayTag& SlotTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		const FGameplayTag& PrevSlot = GetInputTagFormSpec(*AbilitySpec);//技能之前装配的插槽
		const FGameplayTag& Status = GetStatusTagFromSpec(*AbilitySpec);//当前技能的状态标签
		//判断技能的状态，技能状态只有在已装配或解锁的状态才可以装配
		const FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
		if (Status == GameplayTags.Abilities_Status_Equipped||Status == GameplayTags.Abilities_Status_Unlocked)
		{
			ClearAbilitiesofSlot(SlotTag);//通过技能的输入标签清除插槽的技能
			ClearSlot(AbilitySpec);//清除掉当前技能的输入标签
			//将目标插槽的输入标签加到技能实例的动态标签容器中
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(SlotTag);
			//如果状态标签是已解锁，我们需要将其修改为装配状态
			if (Status.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
			{
				AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(GameplayTags.Abilities_Status_Unlocked);
				AbilitySpec->GetDynamicSpecSourceTags().AddTag(GameplayTags.Abilities_Status_Equipped);
			}
			ClientEquipAbility(AbilityTag,Status,SlotTag,PrevSlot);
			MarkAbilitySpecDirty(*AbilitySpec);//立即复制到每个客户端
		}
	}
}

void UAureAbilitySystemComponentBase::ClientEquipAbility_Implementation(const FGameplayTag& AbilityTag,const FGameplayTag& Status, const FGameplayTag& SlotTag ,const FGameplayTag& PreviousSlot)
{
	AbilityEquippedDelegate.Broadcast(AbilityTag,Status,SlotTag,PreviousSlot);
}

void UAureAbilitySystemComponentBase::ClearSlot(FGameplayAbilitySpec* AbilitySpec)
{
	const FGameplayTag Slot =GetInputTagFormSpec(*AbilitySpec);
	AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(Slot);
	MarkAbilitySpecDirty(*AbilitySpec);
}

void UAureAbilitySystemComponentBase::ClearAbilitiesofSlot(const FGameplayTag& SlotTag)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& Ability:GetActivatableAbilities())
	{
		if (AbilityHasSlot(&Ability,SlotTag))
		{
			ClearSlot(&Ability);
			// if (Ability.GetDynamicSpecSourceTags().HasTagExact(PreviousSlot))
			// {
			// 	ClearSlot(&Ability);
			// }
		}
	}
}

bool UAureAbilitySystemComponentBase::AbilityHasSlot(FGameplayAbilitySpec* AbilitySpec, const FGameplayTag& SlotTag)
{
	for (FGameplayTag Tag: AbilitySpec->GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTagExact(SlotTag))
		{
			return true;
		}
	}
	return false;
}

void UAureAbilitySystemComponentBase::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
	{
        FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
        if (const UAureGameplayAbility* AureAbility = Cast<UAureGameplayAbility>(AbilitySpec.Ability))
        {
        	
        	AbilitySpec.GetDynamicSpecSourceTags().AddTag(AureAbility->StartupInputTag);//设置技能激活输入标签
        	AbilitySpec.GetDynamicSpecSourceTags().AddTag(FAureGameplayTags::Get().Abilities_Status_Equipped);//设置技能激活输入标签，将技能状态设置为已装备
        	//激活能力但不应用
            GiveAbility(AbilitySpec);
        }

		//激活并应用一次
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}

	bStartupAbilitiesGiven = true;
	AbilityGivenDelegate.Broadcast();
}

void UAureAbilitySystemComponentBase::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : StartupPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
		GiveAbilityAndActivateOnce(AbilitySpec);
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

void UAureAbilitySystemComponentBase::ForEachAbility(const FForEachAbility& AbilityDelegate)
{
	//使用域锁将此作用域this的内容锁定（无法修改），在遍历结束后解锁，保证线程安全
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& Ability:GetActivatableAbilities())
	{
		//运行绑定在技能实例上的委托，若失败则返回false
		if (!AbilityDelegate.ExecuteIfBound(Ability))
		{
			UE_LOG(LogAure, Warning, TEXT("在函数[%hs]运行失败"), __FUNCTION__)
		}
	}
}

void UAureAbilitySystemComponentBase::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	//判断Avtor是否基础角色接口
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		//判断是否有用于可分配的点数
		if (IPlayerInterface::Execute_GetAttributesPoints(GetAvatarActor())>0)
		{
			ServerUpgradeAttribute(AttributeTag);
		}
	}
}

void UAureAbilitySystemComponentBase::ServerUpgradeAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	//创建一个事件数据
	FGameplayEventData Payload;
	Payload.EventTag =AttributeTag;
	Payload.EventMagnitude =1.0f;

	//向自身发送事件，通过被动技能接受属性家电
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),AttributeTag,Payload);

	//判断Avatar是否基础角色接口
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		//减少一份属性点数
		IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(),-1);
	}
}

FGameplayTag UAureAbilitySystemComponentBase::GetAbilityTagFormSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (const FGameplayTag& Tag : AbilitySpec.Ability->GetAssetTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UAureAbilitySystemComponentBase::GetInputTagFormSpec(const FGameplayAbilitySpec& InputSpec)
{
	if (InputSpec.Ability)
	{
		for (const FGameplayTag& Tag : InputSpec.GetDynamicSpecSourceTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UAureAbilitySystemComponentBase::GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	//从技能实例的动态标签容器中遍历所有标签
	for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))//查找标签中的状态标签
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayAbilitySpec* UAureAbilitySystemComponentBase::GetSpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock ActiveScopeLoc(*this);//域锁 ，确保在函数执行期间不会被其他线程修改
	//遍历已经应用的技能
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
        for (FGameplayTag Tag :AbilitySpec.Ability.Get()->GetAssetTags())
        {
	        if (Tag.MatchesTag(AbilityTag))
	        {
		        return &AbilitySpec;
	        }
        }
	}
	return nullptr;
}

void UAureAbilitySystemComponentBase::UpdateAbilityStatuses(int32 Level)
{
	//从GameMode获取到技能配置数据
	UAbilityInfo* AbilityInfo = UAureAbilitySysTEM_BFL::GetAbilityInfo(GetAvatarActor());
	for (const FAureAbilityInfo& Info : AbilityInfo->AbilityInfo)
	{
		if (!Info.AbilityTag.IsValid()) continue;//如果没有技能标签，取消执行
		if (Level<Info.LevelRequirement) continue;//如果当前等级未达到所需等级，取消执行
		//判断ASC中是否存在当前技能实例
		if (GetSpecFromAbilityTag(Info.AbilityTag) == nullptr)
		{
		  //如果没有技能实例，将应用一个新的技能实例
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Info.Ability,1);
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(FAureGameplayTags::Get().Abilities_Status_Eligible);
			GiveAbility(AbilitySpec);
			//设置当前技能立即复制到每个客户端
			MarkAbilitySpecDirty(AbilitySpec);
			ClientUpdateAbilityStatus(Info.AbilityTag,FAureGameplayTags::Get().Abilities_Status_Eligible,AbilitySpec.Level);
		}
	}
}

bool UAureAbilitySystemComponentBase::GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag,
	FString& OutDescription, FString& OutNextLevelDescription)
{
	//如果当前技能处于锁定状态，将无法获取到对应的技能描述
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		if (UAureGameplayAbility* AureGameplayAbility = Cast<UAureGameplayAbility>(AbilitySpec->Ability))
		{
			OutDescription = AureGameplayAbility->GetDescription(AbilitySpec->Level);
			OutNextLevelDescription = AureGameplayAbility->GetNextLevelDescription(AbilitySpec->Level + 1);
			return true;
		}
	}
	//如果技能是锁定状态，将显示锁定技能描述,当技能标签未设置时，则设置为空，返回空白内容
	UAbilityInfo* AbilityInfo = UAureAbilitySysTEM_BFL::GetAbilityInfo(GetAvatarActor());
	if (!AbilityTag.IsValid()||AbilityTag.MatchesTagExact(FAureGameplayTags::Get().Abilities_None))
	{
		OutDescription = FString();
	}
	else
	{
		OutDescription = UAureGameplayAbility::GetLockedDescription(AbilityInfo->GetAbilityInfoByTag(AbilityTag).LevelRequirement);
	}
	OutNextLevelDescription = FString();
	return false;
}

void UAureAbilitySystemComponentBase::SeverDemotionSpellPoint_Implementation(const FGameplayTag& AbilityTag)
{
	//获取技能实例
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		//增加一个可分配的技能点数
		if (GetAvatarActor()->Implements<UPlayerInterface>())
		{
			IPlayerInterface::Execute_AddToSkillPoints(GetAvatarActor(),1);
		}
		//获取状态标签
		FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
		FGameplayTag StatusTag = GetStatusTagFromSpec(*AbilitySpec);
		//依据状态标签处理
		if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped)||StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
		{
           AbilitySpec->Level -= 1;
           if (AbilitySpec->Level < 1)
           {
	           //技能小于1级，当前技能将无法装配，直接设置为可解锁状态
           	  AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(GameplayTags.Abilities_Status_Equipped);
           	  AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(GameplayTags.Abilities_Status_Unlocked);
           	  AbilitySpec->GetDynamicSpecSourceTags().AddTag(GameplayTags.Abilities_Status_Eligible);
           	  StatusTag = GameplayTags.Abilities_Status_Eligible;

           	const FGameplayTag& PreviousSlot = GetInputTagFormSpec(*AbilitySpec);
           	ClearSlot(AbilitySpec);
           	ClientEquipAbility(AbilityTag,StatusTag,FGameplayTag(),PreviousSlot);
           }
		}
		//广播技能状态修改
		ClientUpdateAbilityStatus(AbilityTag,StatusTag,AbilitySpec->Level);
		//设置当前技能立即复制到每个客户端
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UAureAbilitySystemComponentBase::SeverSpendSpellPoint_Implementation(const FGameplayTag& AbilityTag)
{
	//获取技能实例
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		//减少一个可分配的技能点数
		if (GetAvatarActor()->Implements<UPlayerInterface>())
		{
			IPlayerInterface::Execute_AddToSkillPoints(GetAvatarActor(),-1);
		}
		//获取状态标签
		FAureGameplayTags GameplayTags = FAureGameplayTags::Get();
		FGameplayTag StatusTag = GetStatusTagFromSpec(*AbilitySpec);
		//依据状态标签处理
		if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
		{
			//如果是可解锁状态，则技能升级，状态从可解锁切换为已解锁
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(GameplayTags.Abilities_Status_Eligible);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(GameplayTags.Abilities_Status_Unlocked);
			StatusTag = GameplayTags.Abilities_Status_Unlocked;
			
			AbilitySpec->Level+=1;
		}
		else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked)||StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
		{
		
			AbilitySpec->Level+=1;
		}
		//广播技能状态修改
		ClientUpdateAbilityStatus(AbilityTag,StatusTag,AbilitySpec->Level);
		//设置当前技能立即复制到每个客户端
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UAureAbilitySystemComponentBase::ClientUpdateAbilityStatus_Implementation(const FGameplayTag& AbilityTag,
                                                                               const FGameplayTag& StatusTag, const int32 AbilityLevel)
{
	AbilityStatusChangedDelegate.Broadcast(AbilityTag,StatusTag,AbilityLevel);
}


void UAureAbilitySystemComponentBase::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                         const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
}
