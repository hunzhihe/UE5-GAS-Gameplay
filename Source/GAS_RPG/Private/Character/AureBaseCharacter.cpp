// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AureBaseCharacter.h"

// Sets default values
AAureBaseCharacter::AAureBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAureBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AAureBaseCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

// Called to bind functionality to input
//void AAureBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);

//}

