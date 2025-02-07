// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AureAssetManager.generated.h"




/**
 * 
 */
UCLASS()
class GAS_RPG_API UAureAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UAureAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;
};
