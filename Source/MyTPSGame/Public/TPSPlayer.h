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

	// On ���ξ �ٴ� ��� : �ݹ�, �̺�Ʈ�� �ܺο��� ȣ��Ǵ� �Լ��϶� ����Ѵ�.
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


	// �ѱ� ��ȯ bool
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = PlayerSettings)
	bool bChooseGrenadeGun;


	void ChooseGun(bool bGrenade);

	// �������忡�� ������ �����ϰ� �ʹ�. Crosshair, Sniper
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UUserWidget> corsshairFactory;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		TSubclassOf<class UUserWidget> sniperFactory;


	// TsubclassOf�� ���� �������Ʈ�� �ҷ��ͼ� �־���� �ϱ� ������ 
	// �ݵ�� UPROPERTY ��ũ�θ� �ۼ� �ؾ��Ѵ�. (��Ÿ��(�𸮾� ����)�� �𸮾󿡰� ������Ѿ� �ϱ� ����)
	UPROPERTY()
	class UUserWidget* crossHairUI;

	UPROPERTY()
	class UUserWidget* sniperUI;



	// 1��Ű�� 2��Ű�� ���� (�ѱ�ü)�Է�ó���� �ϰ�ʹ�.
	void OnActionGrenade();
	void OnActionSniper();

	// Zoom in , Zoom out ����
	void OnActionZoomIn();
	void OnActionZoomOut();


	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UParticleSystem* bulletImpactFactory;


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UAnimMontage* fireMontageFactory;


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class USoundBase* fireSound;


};
