// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PlayerComponent), meta = (BlueprintSpawnableComponent))
class TPSPROJECT_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	UPlayerMove();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Look(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);
	
	void Run();

	void Jump();
	
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	// 걷기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;

	// 달리기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IC_tpsPlayer;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_tpsLook;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_tpsMove;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_tpsJump;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_tpsRun;
};
