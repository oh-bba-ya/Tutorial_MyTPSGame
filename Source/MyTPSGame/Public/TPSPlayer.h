// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class MYTPSGAME_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerSettings)
		class UCameraComponent* cameraComp;


	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class ABulletActor> bulletFactory;

	// On 접두어가 붙는 경우 : 콜백, 이벤트등 외부에서 호출되는 함수일때 사용한다.
	void OnAxisHorizaontal(float value);
	void OnAxisVertical(float value);
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnActionJump();
	void OnActionFirePressed();
	void OnActionFireReleased();
	void DoFire();


	FVector direction;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		float walkSpeed = 600;



	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = PlayerSettings)
		class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerSettings)
		class UStaticMeshComponent* sniperMeshComp;


	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	float fireInterval = 0.5f;


	FTimerHandle fireTimerHandle;


	// 총기 변환 bool
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = PlayerSettings)
	bool bChooseGrenadeGun;


	void ChooseGun(bool bGrenade);

	// 위제공장에서 위젯을 생성하고 싶다. Crosshair, Sniper
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UUserWidget> corsshairFactory;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UUserWidget> sniperFactory;


	// TsubclassOf를 통해 블루프린트를 불러와서 넣어줘야 하기 때문에 
	// 반드시 UPROPERTY 매크로를 작성 해야한다. (런타임(언리얼 실행)에 언리얼에게 노출시켜야 하기 때문)
	UPROPERTY()
	class UUserWidget* crossHairUI;

	UPROPERTY()
	class UUserWidget* sniperUI;



	// 1번키와 2번키에 대한 (총교체)입력처리를 하고싶다.
	void OnActionGrenade();
	void OnActionSniper();

	// Zoom in , Zoom out 구현
	void OnActionZoomIn();
	void OnActionZoomOut();


	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UParticleSystem* bulletImpactFactory;


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UAnimMontage* fireMontageFactory;


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class USoundBase* fireSound;


};
