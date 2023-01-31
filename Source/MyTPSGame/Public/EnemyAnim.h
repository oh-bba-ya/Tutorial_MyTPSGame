// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"   // �ݵ�� �ҷ��� ������ϵ��� generated.h ���� ���� �ۼ�����.
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYTPSGAME_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()


public:

	// EnemyFSM��  Enum Ŭ������ ����ϱ� ���� ��������� �ҷ�����.
	// Enum Ŭ������ �ٷ� ����ϱ� ������ ���漱���� �ƴ� ������ ��������� �ҷ����Ѵ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyState state;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAttackPlay = false;

	UPROPERTY()
	class AEnemy* me;		// Getowner : caching


	UFUNCTION(BlueprintCallable)
		void OnEndAttackAnimation();
	
};
