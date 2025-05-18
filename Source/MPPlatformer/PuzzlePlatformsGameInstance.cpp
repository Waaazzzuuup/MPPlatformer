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
