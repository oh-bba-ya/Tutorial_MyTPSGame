// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"   // 반드시 불러올 헤더파일들은 generated.h 파일 위에 작성하자.
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYTPSGAME_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()


public:

	// EnemyFSM의  Enum 클래스를 사용하기 위해 헤더파일을 불러오자.
	// Enum 클래스는 바로 사용하기 때문에 전방선언이 아닌 위에서 헤더파일을 불러야한다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyState state;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAttackPlay = false;

	UPROPERTY()
	class AEnemy* me;		// Getowner : caching


	UFUNCTION(BlueprintCallable)
		void OnEndAttackAnimation();
	
};
