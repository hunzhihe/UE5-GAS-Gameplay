// 关于GAS系统的学习


#include "Player/AurePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAurePlayerController::AAurePlayerController()
{
	//复制操作
	bReplicates = true;
}

void AAurePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
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
//光标追踪，涉及获取光标下的点击结果，
void AAurePlayerController::CursorTrace()
{
    FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
    if (!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
    /**这里存在这几种情况：
     *1.LastActor和thisActor都是空指针，即光标从没放在目标身上，无操作
     *2.lastActor为空，thisActor不为空，即第一次将光标放在目标上，操作高亮显示目标
     *3.lastActor不为空，thisActor为空，即光标离开目标，操作清除高亮显示
     *4.LastActor和thisActor都存在，即从一个目标移到另外一个目标，操作，取消上一个目标高亮，显示下一个目标高亮
     *5.LastActor和thisActor都存在，但是是同一个目标，无操作。
     *
     *
     *
     * 
     */
    if (LastActor == nullptr)
    {
	    if (ThisActor != nullptr)
	    {
		    //状态2
	    	ThisActor->HighlightActor();
	    }
	    else
	    {
		    //状态1，不操作
	    }
    }
    else//lastActor不为空指针
    {
	    if (ThisActor == nullptr)
	    {
		    //状态3
	    	LastActor->UnHighlightActor();
	    }
	    else//
	    {
	    	//状态4
		    if (LastActor!=ThisActor)
		    {
			    LastActor->HighlightActor();
		    	ThisActor->HighlightActor();
		    	
		    }
	    	else
	    	{
	    		//状态5
	    	}
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

	UEnhancedInputComponent* EnhancedInputComponent =CastChecked<UEnhancedInputComponent>(InputComponent);
	//玩家移动绑定到组件上
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAurePlayerController::Move);
}
