#include "Components/Button.h"

#include "MainMenu.h"


bool UMainMenu::Initialize()
{
	bool IsSuperInitialized = Super::Initialize();
	if (!IsSuperInitialized) return false;

	if(!ensure(BtnHost!=nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::BtnHostClicked);

	if(!ensure(BtnJoin!=nullptr)) return false;
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::BtnJoinClicked);
	
	return true;
}

void UMainMenu::BtnHostClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("IM BOUT TO HOST IM A SERVER"))
}

void UMainMenu::BtnJoinClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("IM BOUT TO JOIN IM A GAYMER"))
}
