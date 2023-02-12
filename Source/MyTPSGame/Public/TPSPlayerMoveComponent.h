// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSPlayerBaseComponent.h"
#include "TPSPlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTPSGAME_API UTPSPlayerMoveComponent : public UTPSPlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTPSPlayerMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// TPSPlayer.h ���Ͽ� �����ϴ� SetupPlayerInputComponent �Լ��� ����ٿ��ֱ� �ؿͼ� �̸��� �����ߴ�.
	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;


	//====================== Move ���� �Լ� ==============================

// On ���ξ �ٴ� ��� : �ݹ�, �̺�Ʈ�� �ܺο��� ȣ��Ǵ� �Լ��϶� ����Ѵ�.
	void OnAxisHorizaontal(float value);
	void OnAxisVertical(float value);
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnActionJump();
	void OnActionRunPressed();
	void OnActionRunReleased();
	void OnActionCrouchPressed();
	void OnActionCrouchReleased();

	float speedRun = 600;
	float speedWalk = 400;
	float speedCrouch = 200;


	FVector direction;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float walkSpeed = 600;

	//=========================================================
};
