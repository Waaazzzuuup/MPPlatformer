#include "LobbyGameMode.h"

#include "PuzzlePlatformsGameInstance.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayers++;
	if (NumberOfPlayers >= 2)
	{
		UEngine* Engine = GetGameInstance()->GetEngine();
		if (!ensure(Engine!=nullptr)) return;
		Engine->AddOnScreenDebugMessage(0,3, FColor::Blue,
			FString::Printf(TEXT("Got enough players! Connecting to game in 10 seconds...")));
		
		UWorld* World = GetWorld();
		if (!ensure(World!=nullptr)) return;
		World->GetTimerManager().SetTimer(StartGameTimer, this, &ALobbyGameMode::StartGame, 3.0f, false, 10.0f);
	}
}


void ALobbyGameMode::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Travelling to server with the game map..."));

	UPuzzlePlatformsGameInstance* PPGI = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	if (PPGI==nullptr) return;
	PPGI->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;
	
	// from GameModeBase, enables seamless travel
	// basically, ports all clients to a "light" map (loading screen) and connects them to actual second map
	// non-seamless disconnects all players from one map and tells them to connect to second map
	bUseSeamlessTravel = true;
	
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonMap?listen");
}


void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	NumberOfPlayers--;
}

