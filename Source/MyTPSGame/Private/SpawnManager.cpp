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

	// ������ �ð��Ŀ� ������ �Լ��� ȣ���ϰ� �ʹ�.
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
	// ���� ���� ������ ��ǥ�������� �۴ٸ� ����� �ʹ�.
	if (makeCount < makeTargetCount) {
		UE_LOG(LogTemp, Warning, TEXT("Make"));
		makeCount++;

		// �� ���忡�� ������ ��ġ��   ���� �����ϰ� �ʹ�.
		int rand = FMath::RandRange(0, spawnList.Num() - 1);

		// ���࿡ ������ ���� �ε����� ���� �ε����� ���ٸ� �ٽ� ���� ���ϰ� �ʹ�.
		if (rand == prevRandIndex) {
			rand = (rand + 1) % spawnList.Num();
		}

		FVector loc = spawnList[rand]->GetActorLocation();
		FRotator rot = spawnList[rand]->GetActorRotation();

		// ���� 50% Ȯ���̶�� enemyFactory1, �׷��� �ʴٸ� enemyFactory2�� SpawnActor�ϰ�ʹ�.		
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

	// ������ �ð��Ŀ� ������ �Լ��� ȣ���ϰ� �ʹ�.
	int randTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(timerHandleMakeEnemy, this, &ASpawnManager::MakeEnemy, randTime, false);
	
}

