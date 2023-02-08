// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYTPSGAME_API UTPSPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimProperty)
		float forwardVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimProperty)
		float rightVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimProperty)
		bool isInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimProperty)
		bool isCrouching;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AnimProperty)
		class UAnimMontage* fireMontageFactory;

	UFUNCTION()
	void OnFire();

};
