#include "PuzzlePlatformsGameInstance.h"

// probably isnt needed
//#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

const static FName SESSION_NAME = TEXT("MySessionGame");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Called a constructor PPGameInstance"));
	// find a BP child of some C++ class (or any BP)
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	// it is some complex object, but we can extract a class to a variable
	MenuClass = MenuBPClass.Class;
	if (!ensure(MenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("ERROR: Cant find class %s"), *MenuBPClass.Class->GetName());

	const ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	// it is some complex object, but we can extract a class to a variable
	GameMenuClass = GameMenuBPClass.Class;
	if (!ensure(GameMenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("ERROR: Cant find class %s"), *GameMenuBPClass.Class->GetName());
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Called Initialize PPGameInstance"));
	
	OSS = IOnlineSubsystem::Get();
	if(OSS!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found OSS: %s"), *OSS->GetSubsystemName().ToString());
		// we get a shared pointer to the interface here
		SessionInterface = OSS->GetSessionInterface();
		// shared pointer null check (?)
		if (SessionInterface.IsValid())
		{
			// bind delegates there, we have a pointer
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
		}
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

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
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


void UPuzzlePlatformsGameInstance::CreateSession()
{
	if(SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Called CreateSession"));
		FOnlineSessionSettings MySessionSettings;
		// this is async, it calls a delegate when created; delegate binds in Init()
		SessionInterface->CreateSession(0,SESSION_NAME, MySessionSettings);
	}
}


// host now creates a session, and we already know the pointer to it (shared pointer)
void UPuzzlePlatformsGameInstance::Host()
{
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


void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu!=nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0,5,FColor::Green,FString::Printf(TEXT("Joining %s..."), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
	
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


