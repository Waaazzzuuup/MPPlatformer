#include "LobbyGameMode.h"

#include "GameMapsSettings.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayers++;
	if (NumberOfPlayers >= 2)
	{
		UWorld* World = GetWorld();
		if (!ensure(World!=nullptr)) return;
		// from GameModeBase, enables seamless travel
		// basically, ports all clients to a "light" map (loading screen) and connects them to actual second map
		// non-seamless disconnects all players from one map and tells them to connect to second map
		bUseSeamlessTravel = true;
		
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonMap?listen");
		for (int i=0; i<9999; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), i);
		}
	}
}


void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	NumberOfPlayers--;
}
