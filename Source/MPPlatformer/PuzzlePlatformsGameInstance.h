#pragma once
// global engine includes
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h" // needed here for shared pointer IOnlineSessionPtr 
// local code includes
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuSystem/MenuInterface.h"
// generated mess
#include "PuzzlePlatformsGameInstance.generated.h"

// gotta inherit from an interface to use it (create an implementation)
UCLASS()
class MPPLATFORMER_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformsGameInstance( const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	// this is now an override function from the interface
	UFUNCTION(Exec)
	void Host(FString ServerName) override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	UFUNCTION(Exec)
	void ReturnToMainMenu() override;

	UFUNCTION(Exec)
	void QuitGame() override;

	UFUNCTION(Exec)
	void RefreshServerList() override;

	UFUNCTION(Exec)
	void TestConsole();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> GameMenuClass;
	class UMainMenu* Menu;
	class UGameMenu* GameMenu;
	IOnlineSubsystem* OSS;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	// callbacks to IOnlineSession delegates
	void OnCreateSessionComplete(FName SessionName, bool Succeeded);
	void OnDestroySessionComplete(FName SessionName, bool Succeeded);
	void OnFindSessionsComplete(bool Succeeded);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	FString DesiredServerName;
	void CreateSession();
};
