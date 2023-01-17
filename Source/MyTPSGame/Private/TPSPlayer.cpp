// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BulletActor.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"


// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SKM_Quinn ��� : /Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'



	// 1. �ܰ��� �ش��ϴ� ������ �о���� �ʹ�. (ConstructorHelpers : �����ڿ����� ��밡��)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh (TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	
	// 2. �о� ���� �� �����ߴٸ�
	if (tempMesh.Succeeded()) {
		// 3. Mesh�� �����ϰ� �ʹ�.
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		// 4. Transform�� �����ϰ� �ʹ�.
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0,-90,0));
	}

	// ��������������Ʈ�� �����ϰ� �ʹ�.
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));

	// ���������� ��Ʈ ������Ʈ�� ���̰�
	springArm->SetupAttachment(RootComponent);

	springArm->SetRelativeLocation(FVector(0,50,100));
	springArm->TargetArmLength = 250.0f;

	// ī�޶� ������Ʈ�� �����ϰ� �ʹ�.
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraArmComp"));

	// ī�޶�� �������Ͽ� ���̰� �ʹ�.
	cameraComp->SetupAttachment(springArm);


	// �Է°��� ȸ���� �ݿ��ϰ� �ʹ�.
	bUseControllerRotationYaw = false;
	springArm->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;


	// �Ϲ����� ������Ʈ�� �����Ѵ�.
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComponent"));
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

	if (tempGunMesh.Succeeded()) {
		gunMeshComp->SetSkeletalMesh(tempGunMesh.Object);
		gunMeshComp->SetRelativeLocationAndRotation(FVector(0, 50, 130),FRotator(0,0,0));
	}


	sniperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperMesh"));
	sniperMeshComp->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempSniper(TEXT("/Script/Engine.StaticMesh'/Game/SniperGun/sniper1.sniper1'"));

	if (tempSniper.Succeeded()) {
		sniperMeshComp->SetStaticMesh(tempSniper.Object);
		sniperMeshComp->SetRelativeLocationAndRotation(FVector(0,60,140), FRotator(0,0,0));
		sniperMeshComp->SetRelativeScale3D(FVector(0.15, 0.15, 0.15));
	}

}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	crossHairUI = CreateWidget(GetWorld(), corsshairFactory);
	sniperUI = CreateWidget(GetWorld(), sniperFactory);

	// 1. �¾�� CrosshairUI�� ���̰� �ϰ� �ʹ�.
	crossHairUI->AddToViewport();
	

	ChooseGun(true);


	// 2. �������۰��϶� Zoom In�� �ϸ� crosshairUi X, SniperhairUI 0

	// 3. �������۰��϶� Zoom out�� �ϸ� crosshairUi O, sniperhairUi X

	// 4. �⺻���� �����ϸ� crosshairUi O, sniperhairUi X
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// direction �������� �̵��ϰ� �ʹ�.
	
	FTransform trans(GetControlRotation());
	FVector resultDirection = trans.TransformVector(direction);

	resultDirection.Z = 0;
	resultDirection.Normalize();

	AddMovementInput(resultDirection);

	//direction = FVector::ZeroVector;

}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATPSPlayer::OnAxisHorizaontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATPSPlayer::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ATPSPlayer::OnAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &ATPSPlayer::OnAxisTurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATPSPlayer::OnActionJump);

	// IE_Repeat ������ �ִµ��� ������. (�ʹ��� ���� �ӵ��� ������ ������ Pressed , Released�� ���� ���縦 �����Ѵ�.)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATPSPlayer::OnActionFirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ATPSPlayer::OnActionFireReleased);
	
	// GrenadeGun , SniperGun Key ���ε�
	PlayerInputComponent->BindAction(TEXT("GrenadeGun"), IE_Pressed, this, &ATPSPlayer::OnActionGrenade);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &ATPSPlayer::OnActionSniper);
	
	// Zoom Ű ���ε�
	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Pressed, this, &ATPSPlayer::OnActionZoomIn);
	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Released, this, &ATPSPlayer::OnActionZoomOut);

}

void ATPSPlayer::OnAxisHorizaontal(float value)
{
	direction.Y = value;
}

void ATPSPlayer::OnAxisVertical(float value)
{
	direction.X = value;
}

void ATPSPlayer::OnAxisLookUp(float value)
{
	// Pitch
	AddControllerPitchInput(value);
}

void ATPSPlayer::OnAxisTurnRight(float value)
{
	// Yaw
	AddControllerYawInput(value);
}

void ATPSPlayer::OnActionJump()
{
	Jump();
}

void ATPSPlayer::OnActionFirePressed()
{
	GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, this, &ATPSPlayer::DoFire, fireInterval,true);

	DoFire();
}

void ATPSPlayer::OnActionFireReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(fireTimerHandle);
}

void ATPSPlayer::DoFire()
{
	// SpawnActor

	FTransform t = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
	
	t.SetRotation(FQuat(GetControlRotation()));

	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);

}

void ATPSPlayer::ChooseGun(bool bGrenade)
{
	if (bGrenade && !bChooseGrenadeGun) {
		OnActionZoomOut();
	}

	bChooseGrenadeGun = bGrenade;

	gunMeshComp->SetVisibility(bGrenade);

	sniperMeshComp->SetVisibility(!bGrenade);
}

void ATPSPlayer::OnActionGrenade()
{
	ChooseGun(true);
}

void ATPSPlayer::OnActionSniper()
{
	ChooseGun(false);
}

void ATPSPlayer::OnActionZoomIn()
{
	// �������۰��̶��
	// crosshair�� �Ⱥ��̰� �ϰ�, Ȯ����� ���̰� �Ѵ�.
	if (!bChooseGrenadeGun) {

		// Ȯ�� FOV 30
		cameraComp->SetFieldOfView(30);

		crossHairUI->RemoveFromParent();
		sniperUI->AddToViewport();
	}
}

void ATPSPlayer::OnActionZoomOut()
{
	cameraComp->SetFieldOfView(90);

	// crosshair�� ���̰� �ϰ�, Ȯ����� �Ⱥ��̰� �Ѵ�.
	sniperUI->RemoveFromParent();
	crossHairUI->AddToViewport();
}

