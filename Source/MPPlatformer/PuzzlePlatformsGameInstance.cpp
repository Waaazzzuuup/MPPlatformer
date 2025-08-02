#include "PuzzlePlatformsGameInstance.h"

// probably isnt needed
//#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
// needed for macro "SEARCH_PRESENCE"
#include "Online/OnlineSessionNames.h"
// a new way to get online session interface
//#include "Online.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

const static FName SESSION_NAME = TEXT("GameSession");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("CustomServerName");


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Called a constructor PPGameInstance"));
	// find a BP child of some C++ class (or any BP)
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	// it is some complex object, but we can extract a class to a variable
	MenuClass = MenuBPClass.Class;
	if (!ensure(MenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("ERROR: PPGI: Cant find class MenuClass"));

	const ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	// it is some complex object, but we can extract a class to a variable
	GameMenuClass = GameMenuBPClass.Class;
	if (!ensure(GameMenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("ERROR: PPGI: Cant find class GameMenuClass"));
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Called Initialize PPGameInstance"));
	
	OSS = IOnlineSubsystem::Get();
	if(OSS!=nullptr)
	// UWorld* const World = GetWorld();
	// if (World!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found OSS: %s"), *OSS->GetSubsystemName().ToString());
		// we get a shared pointer to the interface here
		SessionInterface = OSS->GetSessionInterface();

		//new way to get session interface
		// SessionInterface = Online::GetSessionInterface();
		
		// shared pointer null check (?)
		if (SessionInterface.IsValid())
		{
			// bind delegates there, we have a pointer
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);
		}
		// we create an object, then make it a shared ptr
		SessionSearch = MakeShareable(new FOnlineSessionSearch);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: No OSS found"));
	}
}

// this declaration must match a delegate of after-session-creation func 
void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	if(!Succeeded)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Cant create session %s!"), *SessionName.ToString());
		return;
	}
	
	// no ensure cos we can host without menu (console perhaps)
	if (Menu!=nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5,FColor::Green, "Hosting...");

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Lobby?listen");
}

// this declaration must match a delegate of after-session-destoying func 
void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("Called OnDestroyComplete for %s"), *SessionName.ToString());
	if (Succeeded)
	{
		CreateSession();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Not succeeded on destroying session %s"), *SessionName.ToString());
	}
}

// this declaration must match a delegate 
void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	if(!Succeeded)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindSessionComplete returned FALSE"));
		return;
	}

	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND %d Sessions!"), SessionSearch->SearchResults.Num());
		TArray<FServerData> FoundSessionsList;
		for (const FOnlineSessionSearchResult& Result:SessionSearch->SearchResults)
		{
			FServerData CurrentData;
			CurrentData.UserName = Result.Session.OwningUserName;
			CurrentData.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
			CurrentData.CurrentPlayers = CurrentData.MaxPlayers - Result.Session.NumOpenPublicConnections;
			// get session settings
			FString ServerName;
			if(Result.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				CurrentData.ServerName = ServerName;
			}
			else
			{
				CurrentData.ServerName = "UNIDENTIFIED_NAME";
			}
			
			FoundSessionsList.Add(CurrentData); 
		}
		Menu->SetServerList(FoundSessionsList);
	}
	
}

void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName,
	EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Fired a delegate OnJoinSessionComplete"));
	if(!SessionInterface.IsValid()) return;
	
	if(Result!=EOnJoinSessionCompleteResult::Type::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: JoinSession returned not Success!"));
		return;
	}
	
	FString ConnectString;
	bool IsResolved = SessionInterface->GetResolvedConnectString(SESSION_NAME, ConnectString);
	if(!IsResolved)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: SessionInterface cant resolve!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s..."), *ConnectString);
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0,5,FColor::Green,FString::Printf(TEXT("Joining %s..."), *ConnectString));
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	
	PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
}


void UPuzzlePlatformsGameInstance::CreateSession()
{
	if(SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Called CreateSession"));
		// some settings
		FOnlineSessionSettings MySessionSettings;
		// switch for no-steam LAN
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			MySessionSettings.bIsLANMatch = true;
		}
		else
		{
			MySessionSettings.bIsLANMatch = false;
		}
		
		MySessionSettings.NumPublicConnections = 4;
		MySessionSettings.bShouldAdvertise = true;
		MySessionSettings.bUsesPresence = true;
		MySessionSettings.bUseLobbiesIfAvailable = true;
		MySessionSettings.bUseLobbiesVoiceChatIfAvailable = true;
		MySessionSettings.Set(SERVER_NAME_SETTINGS_KEY, FString(DesiredServerName),
			EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		
		// this is async, it calls a delegate when created; delegate binds in Init()
		SessionInterface->CreateSession(0,SESSION_NAME, MySessionSettings);
	}
}

// host now creates a session, and we already know the pointer to it (shared pointer)
void UPuzzlePlatformsGameInstance::Host(FString ServerName)
{
	// refresh this in any case
	DesiredServerName = ServerName;
	if(SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}


void UPuzzlePlatformsGameInstance::Join(uint32 Index)
{
	if(!SessionInterface.IsValid())	return;

	if (Menu!=nullptr)	Menu->Teardown();

	if(!SessionSearch.IsValid()) return;

	bool IsJoined = SessionInterface->JoinSession(0,SESSION_NAME, SessionSearch->SearchResults[Index]);
	if(!IsJoined) UE_LOG(LogTemp, Warning, TEXT("ERROR: SessionInterface->JoinSession cant join"))
}


void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Looking for Sessions..."));
		//SessionSearch->bIsLanQuery = true;
		// Options for search in Steam. 
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 1000;
		// shared ptr -> shared ref (shared ref must have a longer life than session itself)
		// shared ref cant be created if null - it must be always not null
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

// small method for console test of any func
void UPuzzlePlatformsGameInstance::TestConsole()
{
	LoadGameMenu();
}


void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass!=nullptr)) return;
	
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu!=nullptr)) return;

	Menu->Setup();

	// we can just pass the object that implements methods of an interface
	// don't need an actual interface class - that's the point 
	Menu->SetMenuInterface(this);
}


void UPuzzlePlatformsGameInstance::LoadGameMenu()
{
	if (!ensure(GameMenuClass!=nullptr)) return;
	// create the widget itself	
	GameMenu = CreateWidget<UGameMenu>(this, GameMenuClass);
	if (!ensure(GameMenu!=nullptr)) return;
	// make it visible (it can do it by itself)
	GameMenu->Setup();
	// if we use the interface - set an interface after creation
	GameMenu->SetMenuInterface(this);
}


void UPuzzlePlatformsGameInstance::ReturnToMainMenu()
{
	if (GameMenu!=nullptr)
	{
		GameMenu->Teardown();
	}
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MenuLevel", TRAVEL_Absolute);
}


void UPuzzlePlatformsGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

