#include "LobbyGameMode.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayers++;
	if (NumberOfPlayers >= 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got 2 ppl, can't wait to start!"))
	}
}


void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	NumberOfPlayers--;
}
