#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool IsSuperInitialized = Super::Initialize();
	if (!IsSuperInitialized) return false;

	if(!ensure(BtnHost!=nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::BtnHostClicked);

	if(!ensure(BtnOpenJoinMenu!=nullptr)) return false;
	BtnOpenJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::BtnOpenJoinMenuClicked);

	if(!ensure(BtnBack!=nullptr)) return false;
	BtnBack->OnClicked.AddDynamic(this, &UMainMenu::BtnBackClicked);
	
	if(!ensure(BtnJoin!=nullptr)) return false;
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::BtnJoinClicked);
	
	return true;
}


void UMainMenu::SetMenuInterface(IMenuInterface* MI)
{
	MenuInterface = MI;
}


void UMainMenu::Setup()
{
	this->AddToViewport();
	// configure UI navigation mode
	FInputModeUIOnly InputModeBase;
	// TakeWidget returns a SWidget needed for this method
	InputModeBase.SetWidgetToFocus(this->TakeWidget());
	// lock or not lock in window
	InputModeBase.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	PlayerController->SetInputMode(InputModeBase);
	PlayerController->bShowMouseCursor = true;
}


void UMainMenu::Teardown()
{
	UE_LOG(LogTemp, Warning, TEXT("TEARDOWN CALLED"));
	
	FInputModeGameOnly InputModeBase;

	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	PlayerController->SetInputMode(InputModeBase);
	PlayerController->bShowMouseCursor = false;

	this->RemoveFromParent();
}


void UMainMenu::BtnHostClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("IM BOUT TO HOST IM A SERVER"));

	if(MenuInterface!=nullptr)
	{
		// call out a method on the interface
		// implementation is actually in gameinstance class
		MenuInterface->Host();
	}
}

void UMainMenu::BtnOpenJoinMenuClicked() 
{
	if(!ensure(MenuSwitcher!=nullptr)) return;
	// can do it by index, but this is safer
	MenuSwitcher->SetActiveWidget(JoinMenu);
}


void UMainMenu::BtnBackClicked()
{
	if(!ensure(MenuSwitcher!=nullptr)) return;
	// can do it by index, but this is safer
	MenuSwitcher->SetActiveWidget(StartMenu);
}


void UMainMenu::BtnJoinClicked()
{

}
