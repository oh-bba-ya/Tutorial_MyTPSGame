// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyTPSGameGameModeBase.h"
#include "MyTPSGame.h"
AMyTPSGameGameModeBase::AMyTPSGameGameModeBase() {
	// �������� ��� �𸮾� ������Ʈ�� �����Ҷ� (������ ������ ���ϴ°� �ƴ�) �����ȴ�.

	// �α� ���
	//UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	PRINT_LOG(TEXT("%s %s"), TEXT("Hello"), TEXT("World"));
}