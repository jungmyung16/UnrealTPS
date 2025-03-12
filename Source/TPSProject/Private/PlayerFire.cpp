// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include <Camera/CameraComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerAnim.h"

UPlayerFire::UPlayerFire()
{

}

void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	tpsCamComp = me->tpsCamComp;
	gunMeshComp = me->gunMeshComp;
	sniperGunComp = me->sniperGunComp;

	ChangeToSniperGun();

	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);

	_crosshairUI->AddToViewport();
}
void UPlayerFire::SetupInputBinding(UInputComponent* PlayerInputComponent)
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

		EnhancedPlayerInputComponent->BindAction(IA_tpsFire, ETriggerEvent::Triggered, this, &UPlayerFire::Fire);
		EnhancedPlayerInputComponent->BindAction(IA_GrenadeGun, ETriggerEvent::Triggered, this, &UPlayerFire::ChangeToGrenadeGun);
		EnhancedPlayerInputComponent->BindAction(IA_SniperGun, ETriggerEvent::Triggered, this, &UPlayerFire::ChangeToSniperGun);
		EnhancedPlayerInputComponent->BindAction(IA_SniperAim, ETriggerEvent::Started, this, &UPlayerFire::SniperAim);
		EnhancedPlayerInputComponent->BindAction(IA_SniperAim, ETriggerEvent::Completed, this, &UPlayerFire::SniperAim);
	}
}

void UPlayerFire::Fire()
{
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	// Camera Shake 재생
	auto controller = GetWorld()->GetFirstPlayerController();
	controller->PlayerCameraManager->StartCameraShake(cameraShake);

	// 공격 애니메이션 재생
	auto anim = Cast<UPlayerAnim>(me->GetMesh()->GetAnimInstance());
	anim->PlayAttackAnim();

	if (bUsingGrenadeGun) {
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	else {
		FVector startPos = tpsCamComp->GetComponentLocation();
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(me);
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
		if (bHit) {
			FTransform bulletTrans;
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

			auto hitComp = hitInfo.GetComponent();
			if (hitComp && hitComp->IsSimulatingPhysics()) {
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
				hitComp->AddForce(force);
			}

			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy) {
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				enemyFSM->OnDamageProcess();
			}
		}
	}

}

void UPlayerFire::ChangeToGrenadeGun()
{
	bUsingGrenadeGun = true;
	sniperGunComp->SetVisibility(false);
	gunMeshComp->SetVisibility(true);

	me->OnUsingGrenade(bUsingGrenadeGun);
}

void UPlayerFire::ChangeToSniperGun()
{
	bUsingGrenadeGun = false;
	sniperGunComp->SetVisibility(true);
	gunMeshComp->SetVisibility(false);

	me->OnUsingGrenade(bUsingGrenadeGun);
}

void UPlayerFire::SniperAim()
{
	if (bUsingGrenadeGun) {
		return;
	}
	if (bSniperAim == false) {
		bSniperAim = true;
		_sniperUI->AddToViewport();
		tpsCamComp->SetFieldOfView(45.0f);
		_crosshairUI->RemoveFromParent();
	}
	else {
		bSniperAim = false;
		_sniperUI->RemoveFromParent();
		tpsCamComp->SetFieldOfView(90.0f);
		_crosshairUI->AddToViewport();
	}
}