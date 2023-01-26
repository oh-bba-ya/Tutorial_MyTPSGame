// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnim.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPSPlayerAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Owner�� Velocity�� �����ͼ�
	ATPSPlayer* owner = Cast<ATPSPlayer>(TryGetPawnOwner());

	if (owner != nullptr) {
		// rightVelocity , forwardVelocity�� ���ϰ�ʹ�.
		// Vector�� ������ �̿��ؼ� ���Ⱚ�� ���ϰ� �ʹ�.
		FVector velocity = owner->GetVelocity();
		rightVelocity = FVector::DotProduct(velocity, owner->GetActorRightVector());

		forwardVelocity = FVector::DotProduct(velocity, owner->GetActorForwardVector());

		// isInAir�� ���ϰ� �ʹ�.
		isInAir = owner->GetCharacterMovement()->IsFalling();
	}

}

void UTPSPlayerAnim::OnFire() {
	Montage_Play(fireMontageFactory);
	UE_LOG(LogTemp, Warning, TEXT("Do"));
}

