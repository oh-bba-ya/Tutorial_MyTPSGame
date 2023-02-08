// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyTPSGameGameModeBase.h"
#include "MyTPSGame.h"
#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"

AMyTPSGameGameModeBase::AMyTPSGameGameModeBase() {
	// �������� ��� �𸮾� ������Ʈ�� �����Ҷ� (������ ������ ���ϴ°� �ƴ�) �����ȴ�.

	// �α� ���
	//UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	PRINT_LOG(TEXT("%s %s"), TEXT("Hello"), TEXT("World"));
}

void AMyTPSGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �����Ŵ����� makeTargetCount�� ���� ������ �����ϰ� �ʹ�.
	spawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	LevelUp();

}

void AMyTPSGameGameModeBase::LevelUp()
{
	UE_LOG(LogTemp, Warning, TEXT("LevelUp"));
	// �����Ŵ����� makeTargetCount�� �����ϰ� �ʹ�.
	level++;
	spawnManager->makeTargetCount = level;
	
	spawnManager->makeCount = 0;

	// needExp�� �����ϰ� �ʹ�.
	needExp = level;
}

void AMyTPSGameGameModeBase::AddExp(int amount)
{
	UE_LOG(LogTemp, Warning, TEXT("AddExp"));
	exp += amount;

	// ����ġ�� �������� �����ߴ°�.
	if (exp >= needExp) {

		LevelUpProcess();

	}
}

void AMyTPSGameGameModeBase::LevelUpProcess()
{
	// ����Ʈ
	exp -= needExp;
	LevelUp();

	UE_LOG(LogTemp, Warning, TEXT("LevelUpProcess"));

	// ����ġ�� �������� �����ߴ°�.
	if (exp >= needExp) {

		// ������ ����
		FTimerHandle th;
		GetWorldTimerManager().SetTimer(th, this, &AMyTPSGameGameModeBase::LevelUpProcess, 0.2, false);

	}
}
