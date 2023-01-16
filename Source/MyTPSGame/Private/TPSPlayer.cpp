// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BulletActor.h"



// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SKM_Quinn 경로 : /Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'



	// 1. 외관에 해당하는 에셋을 읽어오고 싶다. (ConstructorHelpers : 생성자에서만 사용가능)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh (TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	
	// 2. 읽어 왔을 때 성공했다면
	if (tempMesh.Succeeded()) {
		// 3. Mesh에 적용하고 싶다.
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		// 4. Transform을 수정하고 싶다.
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0,-90,0));
	}

	// 스프링암컴포넌트를 생성하고 싶다.
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));

	// 스프링암을 루트 컴포넌트에 붙이고
	springArm->SetupAttachment(RootComponent);

	springArm->SetRelativeLocation(FVector(0,50,100));
	springArm->TargetArmLength = 250.0f;

	// 카메라 컴포넌트를 생성하고 싶다.
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraArmComp"));

	// 카메라는 스프링암에 붙이고 싶다.
	cameraComp->SetupAttachment(springArm);


	// 입력값을 회전에 반영하고 싶다.
	bUseControllerRotationYaw = false;
	springArm->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;


	// 일반총의 컴포넌트를 생성한다.
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComponent"));
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

	if (tempGunMesh.Succeeded()) {
		gunMeshComp->SetSkeletalMesh(tempGunMesh.Object);
		gunMeshComp->SetRelativeLocationAndRotation(FVector(0, 50, 130),FRotator(0,0,0));
	}

}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// direction 방향으로 이동하고 싶다.
	
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

	// IE_Repeat 누르고 있는동안 나간다. (너무나 빠른 속도로 나가기 때문에 Pressed , Released를 통해 연사를 구현한다.)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATPSPlayer::OnActionFirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ATPSPlayer::OnActionFireReleased);

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

