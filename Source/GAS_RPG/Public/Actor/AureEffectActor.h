// 关于GAS系统的学习

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AureEffectActor.generated.h"


//游戏效果移除状态
UENUM(BlueprintType)
enum class EEffectRemovedPolicy :uint8
{
	
	RemoveOnOverlay,
	DoNotRemoved
};
//游戏效果应用状态
UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlay,
	ApplyOnEndOverlay,
	DoNotApply
	
};

//影响游戏角色属性的物件基类
UCLASS()
class GAS_RPG_API AAureEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAureEffectActor();

	//重叠部分模板
	// UFUNCTION()
	// virtual  void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherCom, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	// UFUNCTION()
 //    virtual  void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UFUNCTION(BlueprintCallable,Category = "Applied  Effects")
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable,Category = "Applied  Effects")
	void OnOverlay(AActor* TargetActor);
	UFUNCTION(BlueprintCallable,Category = "Applied  Effects")
	void OnEndOverlay(AActor* TargetActor);

	// 是否销毁游戏效果(Instant和Duration的GE)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied  Effects")
	bool bDestroyOnEffectApplication = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	bool bApplyEffectsToEnemies = false;
	
	//即时游戏效果类，如药水
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy =EEffectApplicationPolicy::DoNotApply;
	
    //持续游戏效果类，buff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
    EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	//永久游戏效果类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied  Effects")
	EEffectRemovedPolicy InfiniteEffectRemovedPolicy = EEffectRemovedPolicy::RemoveOnOverlay; 


	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveGameplayEffectsHandle;
private:
	// UPROPERTY(VisibleAnywhere) 
	// TObjectPtr<USphereComponent> Sphere;
	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<UStaticMeshComponent> Mesh;
};
