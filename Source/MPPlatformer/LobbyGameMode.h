#pragma once

#include "CoreMinimal.h"
#include "MPPlatformerGameMode.h"
#include "LobbyGameMode.generated.h"


UCLASS()
class MPPLATFORMER_API ALobbyGameMode : public AMPPlatformerGameMode
{
	GENERATED_BODY()

	// an override from GameModeBase
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	uint8 NumberOfPlayers = 1;
};
