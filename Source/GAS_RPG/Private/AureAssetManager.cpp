// 关于GAS系统的学习


#include "AureAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AureGameplayTags.h"

UAureAssetManager& UAureAssetManager::Get()
{
    check(GEngine);
	UAureAssetManager* AureAssetManager =  Cast<UAureAssetManager>(GEngine->AssetManager);

	
	return *AureAssetManager;
}

void UAureAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAureGameplayTags::InitializeNativeGameplayTags();


	//开启TargetData,  
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
