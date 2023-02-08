// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnPoint.h"
#include "MyTPSGame/MyTPSGameGameModeBase.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// 랜덤한 시간후에 적생성 함수를 호출하고 싶다.
	int randTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(timerHandleMakeEnemy,this,&ASpawnManager::MakeEnemy, randTime, false);
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), spawnList);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnManager::MakeEnemy()
{
	// 만약 만든 갯수가 목표갯수보다 작다면 만들고 싶다.
	if (makeCount < makeTargetCount) {
		UE_LOG(LogTemp, Warning, TEXT("Make"));
		makeCount++;

		// 적 공장에서 랜덤한 위치에   적을 생성하고 싶다.
		int rand = FMath::RandRange(0, spawnList.Num() - 1);

		// 만약에 선택한 랜덤 인덱스가 이전 인덱스와 같다면 다시 값을 정하고 싶다.
		if (rand == prevRandIndex) {
			rand = (rand + 1) % spawnList.Num();
		}

		FVector loc = spawnList[rand]->GetActorLocation();
		FRotator rot = spawnList[rand]->GetActorRotation();

		// 만약 50% 확률이라면 enemyFactory1, 그렇지 않다면 enemyFactory2을 SpawnActor하고싶다.		
		int rate = FMath::RandRange(0, 99);
		int levelTargetRate = 50;

		int level = Cast<AMyTPSGameGameModeBase>(GetWorld()->GetAuthGameMode())->level;

		if (level < 3) {
			levelTargetRate = 50;
		}
		else {
			levelTargetRate = -1;
		}

		if (rate < levelTargetRate) {
			GetWorld()->SpawnActor<AEnemy>(enemyFactory1, loc, rot);
		}
		else {
			GetWorld()->SpawnActor<AEnemy>(enemyFactory2, loc, rot);
		}


	}

	// 랜덤한 시간후에 적생성 함수를 호출하고 싶다.
	int randTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(timerHandleMakeEnemy, this, &ASpawnManager::MakeEnemy, randTime, false);
	
}

