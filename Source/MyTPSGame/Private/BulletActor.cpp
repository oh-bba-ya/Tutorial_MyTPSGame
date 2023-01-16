// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/SphereComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(sphereComp);

	sphereComp->SetSphereRadius(13);

	// FName은 대소문자 구분 안함
	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(sphereComp);

	meshComp->SetRelativeScale3D(FVector(0.25,0.25,0.25));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshComp->SetCollisionProfileName(TEXT("NoCollision"));


	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));

	movementComp->SetUpdatedComponent(sphereComp);
	movementComp->InitialSpeed = 1000;
	movementComp->MaxSpeed = 1000;
	movementComp->bShouldBounce = true;
	movementComp->Bounciness = 0.5f;


}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle dieTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(dieTimerHandle, this, &ABulletActor::OnDie, 0.5f);
	
	// Lambda 함수
	// 캡처
	/*
	auto myPlus = [캡처]함수의매개변수->구현
	*/

	/*
	auto myPlus = [this](int a, int b)->int {return a + b; };
	UE_LOG(LogTemp, Warning, TEXT("SUM : %d"), myPlus(10, 20));
	*/


	// 람다 사용
	GetWorld()->GetTimerManager().SetTimer(dieTimerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 2, false);


}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletActor::OnDie()
{
	Destroy();
}

