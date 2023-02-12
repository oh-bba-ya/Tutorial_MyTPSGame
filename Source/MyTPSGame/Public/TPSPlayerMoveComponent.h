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

	// TPSPlayer.h 파일에 존재하는 SetupPlayerInputComponent 함수를 복사붙여넣기 해와서 이름을 수정했다.
	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;


	//====================== Move 관련 함수 ==============================

// On 접두어가 붙는 경우 : 콜백, 이벤트등 외부에서 호출되는 함수일때 사용한다.
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
