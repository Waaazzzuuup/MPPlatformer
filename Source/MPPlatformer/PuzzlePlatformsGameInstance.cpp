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


void UPuzzlePlatformsGameInstance::Host() override
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5,FColor::Green, "HOSTING");

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	
}


void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
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
	
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu!=nullptr)) return;

	Menu->AddToViewport();
	// configure UI navigation mode
	FInputModeUIOnly InputModeBase;
	// TakeWidget returns a SWidget needed for this method
	InputModeBase.SetWidgetToFocus(Menu->TakeWidget());
	// lock or not lock in window
	InputModeBase.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	PlayerController->SetInputMode(InputModeBase);
	PlayerController->bShowMouseCursor = true;

	// we can just pass the object that implements methods of an interface
	// don't need an actual interface class - that's the point 
	Menu->SetMenuInterface(this);
}
