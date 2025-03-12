// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryManager.h"
#include "Components/BoxComponent.h"
#include "TPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AVictoryManager::AVictoryManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryManager::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AVictoryManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVictoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVictoryManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	// SetGamePaused를 호출하기 전에 마우스 커서를 활성화
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}

	// 게임 일시 중지
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
