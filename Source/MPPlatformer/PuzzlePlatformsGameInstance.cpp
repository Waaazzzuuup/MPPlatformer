#include "PuzzlePlatformsGameInstance.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Called a constructor"));
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Called an INIT func"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();

	if (!ensure(Engine!=nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0,5,FColor::Green, "HOST EXECUTED");
}
