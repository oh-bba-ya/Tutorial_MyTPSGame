// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyTPSGameGameModeBase.h"
#include "MyTPSGame.h"
#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"

AMyTPSGameGameModeBase::AMyTPSGameGameModeBase() {
	// 생성자의 경우 언리얼 프로젝트를 시작할때 (에디터 실행을 뜻하는게 아님) 생성된다.

	// 로그 출력
	//UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	PRINT_LOG(TEXT("%s %s"), TEXT("Hello"), TEXT("World"));
}

void AMyTPSGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 스폰매니저의 makeTargetCount를 현재 레벨에 설정하고 싶다.
	spawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	LevelUp();

}

void AMyTPSGameGameModeBase::LevelUp()
{
	UE_LOG(LogTemp, Warning, TEXT("LevelUp"));
	// 스폰매니저의 makeTargetCount를 설정하고 싶다.
	level++;
	spawnManager->makeTargetCount = level;
	
	spawnManager->makeCount = 0;

	// needExp도 설정하고 싶다.
	needExp = level;
}

void AMyTPSGameGameModeBase::AddExp(int amount)
{
	UE_LOG(LogTemp, Warning, TEXT("AddExp"));
	exp += amount;

	// 경험치가 레벨업에 도달했는가.
	if (exp >= needExp) {

		LevelUpProcess();

	}
}

void AMyTPSGameGameModeBase::LevelUpProcess()
{
	// 이펙트
	exp -= needExp;
	LevelUp();

	UE_LOG(LogTemp, Warning, TEXT("LevelUpProcess"));

	// 경험치가 레벨업에 도달했는가.
	if (exp >= needExp) {

		// 레벨업 시작
		FTimerHandle th;
		GetWorldTimerManager().SetTimer(th, this, &AMyTPSGameGameModeBase::LevelUpProcess, 0.2, false);

	}
}
