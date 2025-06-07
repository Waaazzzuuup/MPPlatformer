#include "PuzzlePlatformsGameInstance.h"

// probably isnt needed
//#include "UObject/ConstructorHelpers.h"

#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Called a constructor"));
	// find a BP child of some C++ class (or any BP)
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	// it is some complex object, but we can extract a class to a variable
	MenuClass = MenuBPClass.Class;
	if (!ensure(MenuClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("Cant find class %s"), *MenuBPClass.Class->GetName());
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
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
