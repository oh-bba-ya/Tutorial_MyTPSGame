// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSPlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTPSGAME_API UTPSPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTPSPlayerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// ������ ����Ŭ �߰�
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
	// virtual Ű���带 ���� ��ӹ޴� Ŭ�������� �������̵�, �����θ� cpp�� �ȸ���� ���� {} �߰�
	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) {}

	UPROPERTY()
	class ATPSPlayer* me;

};
