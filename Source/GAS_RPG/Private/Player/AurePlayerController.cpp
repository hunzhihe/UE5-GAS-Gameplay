// 关于GAS系统的学习


#include "Player/AurePlayerController.h"

#include "EnhancedInputSubsystems.h"

AAurePlayerController::AAurePlayerController()
{
	//复制操作
	bReplicates = true;
}

void AAurePlayerController::BeginPlay()
{
	Super::BeginPlay();
	//检查输入映射上下文
    check(AuraContext);
   //访问增强输入本地玩家子系统来添加输入映射上下文
	UEnhancedInputLocalPlayerSubsystem* Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    check(Subsystem);
   //通过子系统添加输入映射上下文,后面的0是输入的优先级，
	Subsystem->AddMappingContext(AuraContext,0);

	//是否显示鼠标光标,光标类型默认
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default();

	//输入模式，游戏和UI是一个模式
	FInputModeGameAndUI InputModeData;

	//将鼠标锁定到视口行为设置为不锁定，当光标被捕获到视口时，不隐藏光标
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);


	SetInputMode(InputModeData);
}
