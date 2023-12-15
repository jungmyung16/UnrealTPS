// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �÷��̾��� �̵� �ӵ��� ������ speed�� �Ҵ��ϱ�
	// 1) ���� Pawn ������
	auto ownerPawn = TryGetPawnOwner();
	// 2) �÷��̾�� ĳ�����ϱ�
	auto player = Cast<ATPSPlayer>(ownerPawn);
	// ĳ���ÿ� �����ߴٸ�,
	if (player) {
		// 3) �̵��ӵ� ������
		FVector velocity = player->GetVelocity();
		// 4) �÷��̾��� ���� ���� ������
		FVector forwardVector = player->GetActorForwardVector();
		// 5) speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, velocity);
		// 6) �¿� �̵� �ӵ� �Ҵ��ϱ�
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		// �÷��̾ ���� ���߿� �ִ��� ���θ� ������
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}
void UPlayerAnim::PlayAttackAnim() 
{
	Montage_Play(attackAnimMontage);
}
