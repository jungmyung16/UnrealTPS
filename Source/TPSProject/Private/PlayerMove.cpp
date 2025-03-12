// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"

UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();
	
	// 초기 속도를 걷기로 설정
	moveComp->MaxWalkSpeed = walkSpeed;
}
void UPlayerMove::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UPlayerMove::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (InputValue.X != 0.0f) {
		me->AddControllerYawInput(InputValue.X);
	}
	if (InputValue.Y != 0.0f) {
		me->AddControllerPitchInput(InputValue.Y);
	}
}
void UPlayerMove::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	if (me->Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f)) {
		const FRotator YawRotation(0, me->Controller->GetControlRotation().Yaw, 0);

		if (InputValue.X != 0.0f) {
			// get right vector
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);
			// add movement in that direction
			me->AddMovementInput(RightDirection, InputValue.X);
		}
		if (InputValue.Y != 0.0f) {
			// get forward vector
			const FVector ForwardDirection = YawRotation.Vector();
			me->AddMovementInput(ForwardDirection, InputValue.Y);
		}
	}
}
void UPlayerMove::Run()
{
	auto movement = moveComp;
	if (movement->MaxWalkSpeed > walkSpeed) {
		movement->MaxWalkSpeed = walkSpeed;
	}
	else {
		movement->MaxWalkSpeed = runSpeed;
	}
}
void UPlayerMove::Jump()
{
	me->Jump();
}
void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedPlayerInputComponent != nullptr) {
		APlayerController* PlayerController = Cast<APlayerController>(Cast<ATPSPlayer>(GetOwner())->GetController());
		if (PlayerController != nullptr) {
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (EnhancedSubsystem != nullptr) {
				EnhancedSubsystem->AddMappingContext(IC_tpsPlayer, 1);
			}
		}

		EnhancedPlayerInputComponent->BindAction(IA_tpsLook, ETriggerEvent::Triggered, this, &UPlayerMove::Look);
		EnhancedPlayerInputComponent->BindAction(IA_tpsMove, ETriggerEvent::Triggered, this, &UPlayerMove::Move);
		EnhancedPlayerInputComponent->BindAction(IA_tpsRun, ETriggerEvent::Started, this, &UPlayerMove::Run);
		EnhancedPlayerInputComponent->BindAction(IA_tpsRun, ETriggerEvent::Completed, this, &UPlayerMove::Run);
		EnhancedPlayerInputComponent->BindAction(IA_tpsJump, ETriggerEvent::Triggered, this, &UPlayerMove::Jump);
		//EnhancedPlayerInputComponent->BindAction(IA_tpsJump, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedPlayerInputComponent->BindAction(IA_tpsJump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}