// 关于GAS系统的学习


#include "Player/AurePlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
//#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "AureGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AureAbilitySystemComponentBase.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Input/AureBaseEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAurePlayerController::AAurePlayerController()
{
	//服务器复制操作
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAurePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

    AutoRun();
	
}

void AAurePlayerController::ShowDamagedNumber_Implementation(float Damage,ACharacter*TargetCharacter,bool bIsCritical,bool bIsGeDang)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter,DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(Damage,bIsGeDang,bIsCritical);
	}



	
}

UAureAbilitySystemComponentBase* AAurePlayerController::GetAureBaseASC()
{
	if (AureBaseASC==nullptr)
	{
		AureBaseASC = Cast<UAureAbilitySystemComponentBase>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AureBaseASC;
}

void AAurePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	//设置Yaw
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

    //获取前后和左右方向

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	if(APawn* ControlledPawn =GetPawn<APawn>())
	{

       ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);

		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AAurePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,InputTag.ToString());
	//鼠标左键按下
	if (InputTag.MatchesTagExact(FAureGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor? true : false;
		bHasAutoRuning = false;
		holdTime = 0.f;
	}
}

void AAurePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2,5.f,FColor::Blue,InputTag.ToString());
	//if (GetAureBaseASC() == nullptr) return;
	
	
	if (!InputTag.MatchesTagExact(FAureGameplayTags::Get().InputTag_LMB))
	{
		if (GetAureBaseASC())
		{
			GetAureBaseASC()->AbilityInputTagReleased(InputTag);
			return;
		}

	}
	if (bTargeting||bShiftKeyDown)
	{
		if (GetAureBaseASC())
		
			//点击目标，攻击敌人
			GetAureBaseASC()->AbilityInputTagReleased(InputTag);
		
	}
	 else
	 {
		const APawn* ControlledPawn = GetPawn<APawn>();
	 	if (holdTime<=ShortPresshold && ControlledPawn)
	 	{
	 		//自动寻路
	 		if (UNavigationPath* Navpath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
	 		{
	 			Spline->ClearSplinePoints();
	//
	 			for (const FVector& PointLoc: Navpath->PathPoints)
	 			{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);//为样条曲线添加新点
	 				//DrawDebugSphere(GetWorld(),PointLoc,8.f,8,FColor::Green,false,5.f);
				}
			    if (Navpath->PathPoints.Num() > 0)
			    {
			    	CachedDestination = Navpath->PathPoints[Navpath->PathPoints.Num() - 1];
			    	bHasAutoRuning = true;
			    }

			}
		}
	 	holdTime = 0.f;
	 	bTargeting = false;
	 }
}

void AAurePlayerController::AbilityInputTagHold(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3,5.f,FColor::Green,InputTag.ToString());
	//if (GetAureBaseASC() == nullptr) return;
	
	
	if (!InputTag.MatchesTagExact(FAureGameplayTags::Get().InputTag_LMB))
	{
		if (GetAureBaseASC()){	GetAureBaseASC()->AbilityInputTagHeld(InputTag);}
		
		
			return;
	}
	//鼠标获取到目标或者按Shift;
	if (bTargeting||bShiftKeyDown)
	{
		if (GetAureBaseASC())
		
			//点击目标，攻击敌人
			GetAureBaseASC()->AbilityInputTagHeld(InputTag);
		
	}
	else
	{
		holdTime += GetWorld()->GetDeltaSeconds();//统计时间判断点击还是移动

		
		//拾取鼠标点击位置
		//FHitResult Hit;
		
		if (Hit.bBlockingHit)
		{
			CachedDestination = Hit.ImpactPoint;
		}
			
		
		//获取当前控制对象，并计算角色朝向
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination- ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

//鼠标追踪，涉及获取光标下的点击结果，
void AAurePlayerController::CursorTrace()
{
    
	GetHitResultUnderCursor(ECC_Visibility,false,Hit);
    if (!Hit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(Hit.GetActor());
    /**这里存在这几种情况：
     *1.LastActor和thisActor都是空指针，即光标从没放在目标身上，无操作
     *2.lastActor为空，thisActor不为空，即第一次将光标放在目标上，操作高亮显示目标
     *3.lastActor不为空，thisActor为空，即光标离开目标，操作清除高亮显示
     *4.LastActor和thisActor都存在，即从一个目标移到另外一个目标，操作，取消上一个目标高亮，显示下一个目标高亮
     *5.LastActor和thisActor都存在，但是是同一个目标，无操作。
     */
    // if (LastActor == nullptr)
    // {
	   //  if (ThisActor != nullptr)
	   //  {
		  //   //状态2
	   //  	ThisActor->HighlightActor();
	   //  }
	   //  else
	   //  {
		  //   //状态1，不操作
	   //  }
    // }
    // else//lastActor不为空指针
    // {
	   //  if (ThisActor == nullptr)
	   //  {
		  //   //状态3
	   //  	LastActor->UnHighlightActor();
	   //  }
	   //  else//
	   //  {
	   //  	//状态4
		  //   if (LastActor!=ThisActor)
		  //   {
			 //    LastActor->HighlightActor();
		  //   	ThisActor->HighlightActor();
		  //   	
		  //   }
	   //  	else
	   //  	{
	   //  		//状态5
	   //  	}
	   //  }
    // }
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();

	}
 
	
}

void AAurePlayerController::AutoRun()
{
	if (!bHasAutoRuning) return;
	if (APawn* ControlledPawnn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawnn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControlledPawnn->AddMovementInput(Direction,1.f);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination<=AutoRunAcceptRadius)
		{
			bHasAutoRuning = false;
		}
		
	}
}

void AAurePlayerController::BeginPlay()	
{
	Super::BeginPlay();
	//检查输入映射上下文
    check(AuraContext);
   //访问增强输入本地玩家子系统来添加输入映射上下文
	UEnhancedInputLocalPlayerSubsystem* Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    //check(Subsystem);
   //通过子系统添加输入映射上下文,后面的0是输入的优先级，
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	

	//是否显示鼠标光标,光标类型默认
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//输入模式，游戏和UI是一个模式
	FInputModeGameAndUI InputModeData;

	//将鼠标锁定到视口行为设置为不锁定，当光标被捕获到视口时，不隐藏光标
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);


	SetInputMode(InputModeData);
}

//
void AAurePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAureBaseEnhancedInputComponent* EnhancedInputComponent =CastChecked<UAureBaseEnhancedInputComponent>(InputComponent);
	//玩家移动绑定到组件上
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAurePlayerController::Move);

	EnhancedInputComponent->BindAction(ShiftAttackAction,ETriggerEvent::Started,this,&AAurePlayerController::ShiftPressed);
	EnhancedInputComponent->BindAction(ShiftAttackAction,ETriggerEvent::Completed,this,&AAurePlayerController::ShiftReleased);


	
	EnhancedInputComponent->BindAbilityAction(InputConfig,this,&ThisClass::AAurePlayerController::AbilityInputTagPressed,&ThisClass::AAurePlayerController::AbilityInputTagReleased,&ThisClass::AAurePlayerController::AbilityInputTagHold);
	
}
