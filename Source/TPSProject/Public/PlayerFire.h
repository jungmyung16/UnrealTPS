// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerFire.generated.h"

/**
 * 
 */
// 블루프린트에서 PlayerFire를 등록하기 위해 검색하면 나오지 않음
// -> PlayerFire 컴포넌트가 블루프린트에서 사용할 수 있도록 설정해 주어야함
UCLASS(ClassGroup = (PlayerComponent), meta = (BlueprintSpawnableComponent))
class TPSPROJECT_API UPlayerFire : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public:
	UPlayerFire();

	virtual void BeginPlay() override;

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UCameraComponent* tpsCamComp;

	UPROPERTY()
	class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY()
	class UStaticMeshComponent* sniperGunComp;

public:
	void Fire();

	void ChangeToGrenadeGun();
	void ChangeToSniperGun();

	void SniperAim();

	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;

	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	// 총알 발사 사운드
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* bulletSound;

	// Camera Shake 블루프린트를 저장할 변수
	UPROPERTY(EditDefaultsOnly, Category = CameraMotion)
	TSubclassOf<class UCameraShakeBase> cameraShake;

	bool bUsingGrenadeGun = true;

	bool bSniperAim = false;

	class UUserWidget* _sniperUI;

	class UUserWidget* _crosshairUI;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IC_tpsPlayer;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_tpsFire;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_GrenadeGun;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_SniperGun;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_SniperAim;
};
