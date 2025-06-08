#include "GameMenu.h"
#include "Components/Button.h"


bool UGameMenu::Initialize()
{
	bool IsSuperInitialized = Super::Initialize();
	if (!IsSuperInitialized) return false;

	if(!ensure(BtnCancel!=nullptr)) return false;
	BtnCancel->OnClicked.AddDynamic(this, &UGameMenu::BtnCancelClicked);

	if(!ensure(BtnBackToMainMenu!=nullptr)) return false;
	BtnBackToMainMenu->OnClicked.AddDynamic(this, &UGameMenu::BtnBackToMainMenuClicked);
	
	return true;
}


void UGameMenu::BtnBackToMainMenuClicked()
{
	if(MenuInterface!=nullptr)
	{
		MenuInterface->ReturnToMainMenu();
	}
}


void UGameMenu::BtnCancelClicked()
{
	Teardown();
}
