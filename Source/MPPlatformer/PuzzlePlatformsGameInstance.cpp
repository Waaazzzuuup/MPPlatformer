#include "PuzzlePlatformsGameInstance.h"

// probably isnt needed
//#include "UObject/ConstructorHelpers.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"
#include "Blueprint/UserWidget.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Called a constructor"));
	// find a BP child of some C++ class (or any BP)
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	// it is some complex object, but we can extract a class to a variable
	MenuClass = MenuBPClass.Class;
	if (!ensure(MenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("Cant find class %s"), *MenuBPClass.Class->GetName());

	const ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	// it is some complex object, but we can extract a class to a variable
	GameMenuClass = GameMenuBPClass.Class;
	if (!ensure(GameMenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("Cant find class %s"), *GameMenuBPClass.Class->GetName());
	
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Called Initialize PPGameInstance"));
	
	OSS = IOnlineSubsystem::Get();
	if(OSS!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND OSS %s"), *OSS->GetSubsystemName().ToString());
		IOnlineSessionPtr SessionInterface = OSS->GetSessionInterface();
		// shared pointer null check (?)
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("FOUND Session Interface"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO OSS"));
	}
}


void UPuzzlePlatformsGameInstance::Host()
{
	// no ensure cos we can host without menu (console perhaps)
	if (Menu!=nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5,FColor::Green, "HOSTING");

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	
}


void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu!=nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0,5,FColor::Green,FString::Printf(TEXT("JOINING %s"), *Address));

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
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5,FColor::Green, "RETURN TO MAIN MENU");

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
