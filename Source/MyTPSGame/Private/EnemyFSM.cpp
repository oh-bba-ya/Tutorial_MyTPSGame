// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "..\Public\EnemyFSM.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"

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

	// me�� ã������.
	me = Cast<AEnemy>(GetOwner());

	hp = maxHP;
	
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
	// 1. �÷��̾ ã�� �ʹ�.
	target = Cast<ATPSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// 2. ���� �÷��̾ ã������
	if (target != nullptr) {
		// 3. �̵����� �����ϰ� �ʹ�.
		// state = EEnemyState::MOVE; <- ���� �ڵ�
		SetState(EEnemyState::MOVE); // SetState �Լ��� ����
	}

}


// �������� ���ؼ� �̵��ϰ� �ʹ�.
// ���������� �Ÿ��� ���ݰ��ɰŸ����
// ���ݻ��·� �����ϰ� �ʹ�.
void UEnemyFSM::TickMove()
{
	// 1. �������� ���ϴ� ������ �����
	// GetOwner() : ActorComponent Ŭ������ ������ Ŭ������ ����Ŵ
	//FVector dir = target->GetActorLocation() - GetOwner();
	FVector dir = target->GetActorLocation() - me->GetActorLocation();   // ��� ����Ұ��̱� ������ me ������ ĳ����

	// 2. �� �������� �̵��ϰ� �ʹ�.
	me->AddMovementInput(dir.GetSafeNormal());

	// 3. ���������� �Ÿ��� ���ݰ��ɰŸ����
	//float dist = target->GetDistanceTo(me);
	//float dist = dir.Size();
	float dist = FVector::Dist(target->GetActorLocation(), me->GetActorLocation());

	if (dist < attackRange) {
		// 4. ���ݻ��·� �����ϰ� �ʹ�.
		//state = EEnemyState::ATTACK;  // ���� �ڵ� ����
		SetState(EEnemyState::ATTACK);
	}
}

// ���� Ÿ�̹� 
void UEnemyFSM::TickAttack()
{
	//static float currentTime;

	// 1. �ð��� �帣�ٰ�
	currentTime += GetWorld()->GetDeltaSeconds();

	// 2. ����ð��� ���ݽð��� �ʰ��ϸ�
	if (!bAttackPlay && currentTime > 0.1f) {
		bAttackPlay = true;
		// 3. ������ �ϰ� (������ ���ݰŸ� �ȿ� �ִ°�?)
		float dist = target->GetDistanceTo(me);
		if (dist <= attackRange) {
			UE_LOG(LogTemp, Warning, TEXT("Enemy Attack"));
		}
	}

	// 4. ���ݵ����� �����ٸ�
	if (currentTime > 2) {
		// 5. ��� ������ �� ������ �Ǵ��ϰ� �ʹ�.
		float dist = target->GetDistanceTo(me);
		if (dist > attackRange) {
			//state = EEnemyState::MOVE;   // ���� �ڵ� ����
			SetState(EEnemyState::MOVE);
		}
		else {
			currentTime = 0;
			bAttackPlay = false;
		}
	}
}

// player->Enemy ����
void UEnemyFSM::TickDamage()
{
	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 1) {
		//state = EEnemyState::MOVE;   // ���� �ڵ� ����
		SetState(EEnemyState::MOVE); 
		currentTime = 0;
	}
}

void UEnemyFSM::TickDie()
{
	currentTime += GetWorld()->GetDeltaSeconds();

	// P = P0 + vt ������ ���� ���� ������ �������� ����ɴ°��� �����غ���.
	FVector p0 = me->GetActorLocation();
	FVector vt = FVector(0, 0, -1) * GetWorld()->GetDeltaSeconds() * 200;

	me->SetActorLocation(p0 + vt);

	if (currentTime > 1) {
		me->Destroy();
	}
}

// �÷��̾�� �¾Ҵ�.
void UEnemyFSM::OnDamageProcess(int damageValue)
{
	// ü���� �Ҹ��ϰ�
	hp -= damageValue;
	// ü���� 0�̵Ǹ�
	if (hp <= 0) {
		// ���°� Die�� ����
		//state = EEnemyState::DIE;    // ���� �ڵ� ����
		SetState(EEnemyState::DIE);
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else {// �׷��� �ʴٸ�
		// Damage�� �޴´�.
		//state = EEnemyState::DAMAGE;   // ���� �ڵ� ����
		SetState(EEnemyState::DAMAGE);

	}

}


void UEnemyFSM::SetState(EEnemyState next)
{
	state = next;
	
	// �� ��ü�� EnemyAnim�� State�� �� State�� �־��ְ� �ʹ�.
	if (me->enemyAnim != nullptr)
	{
		me->enemyAnim->state = this->state;
	}
	
}

