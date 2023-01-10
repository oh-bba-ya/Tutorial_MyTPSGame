// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyTPSGameGameModeBase.h"
#include "MyTPSGame.h"
AMyTPSGameGameModeBase::AMyTPSGameGameModeBase() {
	// 생성자의 경우 언리얼 프로젝트를 시작할때 (에디터 실행을 뜻하는게 아님) 생성된다.

	// 로그 출력
	//UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	PRINT_LOG(TEXT("%s %s"), TEXT("Hello"), TEXT("World"));
}