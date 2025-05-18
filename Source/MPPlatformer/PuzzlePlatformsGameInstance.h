#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

UCLASS()
class MPPLATFORMER_API UPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance( const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;
	
};
