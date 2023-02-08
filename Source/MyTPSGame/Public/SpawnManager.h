// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class MYTPSGAME_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ������ �ð����� ���� ���� ��ġ�� �����ϰ� �ʹ�.
	// -�ּ� , �ִ� �ð�
	UPROPERTY(EditAnywhere)
	TArray<AActor*>spawnList;

	// ������ ������ ���� ��ġ
	int prevRandIndex = -1;

	UPROPERTY(EditAnywhere)
		float minTime = 1;

	UPROPERTY(EditAnywhere)
		float maxTime = 2;

	// - Ÿ�̸� �ڵ�
	FTimerHandle timerHandleMakeEnemy;

	// - �� ���� -> �𸮾�ü
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> enemyFactory1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> enemyFactory2;



	void MakeEnemy();

	// ���� ����
	int32 makeCount;

	// ��ǥ ����
	int32 makeTargetCount;

};
