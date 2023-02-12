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

	// 라이플 사이클 추가
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
	// virtual 키워드를 통해 상속받는 클래스에서 오버라이딩, 구현부를 cpp에 안만들기 위해 {} 추가
	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) {}

	UPROPERTY()
	class ATPSPlayer* me;

};
