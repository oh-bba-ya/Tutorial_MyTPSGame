// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "..\Public\EnemyFSM.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "EnemyAnim.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	
	state = EEnemyState::IDLE;

	// me를 찾아주자.
	me = Cast<AEnemy>(GetOwner());

	hp = maxHP;

	// 캐싱
	ai = Cast<AAIController>(me->GetController());
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	switch (state) {
	case EEnemyState::IDLE:
		TickIdle();
		break;
	case EEnemyState::MOVE:
		TickMove();
		break;
	case EEnemyState::ATTACK:
		TickAttack();
		break;
	case EEnemyState::DAMAGE:
		TickDamage();
		break;
	case EEnemyState::DIE:
		TickDie();
		break;
	default:
		break;
	}


}

void UEnemyFSM::TickIdle()
{
	// 1. 플레이어를 찾고 싶다.
	target = Cast<ATPSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// 2. 만약 플레이어를 찾았으면
	if (target != nullptr) {
		// 3. 이동으로 전이하고 싶다.
		// state = EEnemyState::MOVE; <- 기존 코드
		SetState(EEnemyState::MOVE); // SetState 함수로 변경
	}

}


// 목적지를 향해서 이동하고 싶다.
// 목적지와의 거리가 공격가능거리라면
// 공격상태로 전이하고 싶다.
void UEnemyFSM::TickMove()
{
	// 1. 목적지를 향하는 방향을 만들고
	// GetOwner() : ActorComponent 클래스를 소유한 클래스를 가리킴
	//FVector dir = target->GetActorLocation() - GetOwner();
	FVector dir = target->GetActorLocation() - me->GetActorLocation();   // 계속 사용할것이기 때문에 me 변수에 캐싱함

	// 2. 그 방향으로 이동하고 싶다.
	ai->MoveToLocation(target->GetActorLocation());

	// me->AddMovementInput(dir.GetSafeNormal()); <- 기존 코드 삭제


	// 3. 목적지와의 거리가 공격가능거리라면
	//float dist = target->GetDistanceTo(me);
	//float dist = dir.Size();
	float dist = FVector::Dist(target->GetActorLocation(), me->GetActorLocation());

	if (dist < attackRange) {
		// 4. 공격상태로 전이하고 싶다.
		//state = EEnemyState::ATTACK;  // 기존 코드 삭제
		SetState(EEnemyState::ATTACK);
	}
}

// 공격 타이밍 
void UEnemyFSM::TickAttack()
{
	//static float currentTime;

	// 1. 시간이 흐르다가
	currentTime += GetWorld()->GetDeltaSeconds();

	if (currentTime > attackDelayTime) {
		currentTime = 0;
		me->enemyAnim->bAttackPlay = true;
		UE_LOG(LogTemp, Warning, TEXT("Enemy is Attack"));
	}

	float dist = target->GetDistanceTo(me);
	if (dist > attackRange) {
		SetState(EEnemyState::MOVE);
	}


}

// player->Enemy 공격
void UEnemyFSM::TickDamage()
{
	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 1) {
		//state = EEnemyState::MOVE;   // 기존 코드 삭제
		SetState(EEnemyState::MOVE); 
		currentTime = 0;
	}
}

void UEnemyFSM::TickDie()
{
	// 만약 넘어지는 애니메이션이 끝나지 않았다면
	if (!me->enemyAnim->bEnemyDieEnd) {
		return ;
	}

	currentTime += GetWorld()->GetDeltaSeconds();

	// P = P0 + vt 공식을 통해 적이 죽으면 땅속으로 가라앉는것을 구현해보자.
	FVector p0 = me->GetActorLocation();
	FVector vt = FVector(0, 0, -1) * GetWorld()->GetDeltaSeconds() * 200;

	me->SetActorLocation(p0 + vt);

	if (currentTime > 1) {
		me->Destroy();
	}
}

// 플레이어에게 맞았다.
void UEnemyFSM::OnDamageProcess(int damageValue)
{
	if (ai) {
		ai->StopMovement();
	}

	// 체력을 소모하고
	hp -= damageValue;
	// 체력이 0이되면
	if (hp <= 0) {
		// 상태가 Die로 변함
		me->enemyAnim->bEnemyDieEnd = false;
		// 몽타주의 Die Section을 play 시키고 싶다.
		me->OnMyDamage(TEXT("Die"));
		SetState(EEnemyState::DIE);
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	}
	else {// 그렇지 않다면
		// Damage를 받는다.
		SetState(EEnemyState::DAMAGE);
		if (FMath::RandRange(0, 100) > 50) {
			me->OnMyDamage(TEXT("Damage0"));
		}
		else {
			me->OnMyDamage(TEXT("Damage1"));
		}
	}

}


void UEnemyFSM::SetState(EEnemyState next)
{
	state = next;
	
	// 내 본체의 EnemyAnim의 State에 내 State를 넣어주고 싶다.
	if (me->enemyAnim != nullptr)
	{
		me->enemyAnim->state = this->state;
	}

	currentTime = 0;
	
}

void UEnemyFSM::OnHitEvent()
{
	me->enemyAnim->bAttackPlay = false;

	float dist = target->GetDistanceTo(me);
	if (dist <= attackRange) {
		UE_LOG(LogTemp,Warning, TEXT("Enemy is Attack"));
	}
}

