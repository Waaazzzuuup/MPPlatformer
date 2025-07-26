#include "LobbyGameMode.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumberOfPlayers++;
	if (NumberOfPlayers >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got 3 ppl, cant wait to start!"))
	}
}


void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	NumberOfPlayers--;
}
