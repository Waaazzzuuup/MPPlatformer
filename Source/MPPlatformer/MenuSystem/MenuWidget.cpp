#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* MI)
{
	MenuInterface = MI;
}


void UMenuWidget::Setup()
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


void UMenuWidget::Teardown()
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
