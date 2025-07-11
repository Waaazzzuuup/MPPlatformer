#include "MainMenu.h"

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
// ConstructorHelpers isnt needed for constructor

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer )
{
	const ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	// it is some complex object, but we can extract a class to a variable
	ServerRowClass = ServerRowBPClass.Class;
	if (!ensure(ServerRowClass!=nullptr)) UE_LOG(LogTemp, Warning, TEXT("ERROR: MainMenu: Cant find class ServerRow"));
}


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

	if(!ensure(BtnQuit!=nullptr)) return false;
	BtnQuit->OnClicked.AddDynamic(this, &UMainMenu::BtnQuitClicked);
	
	return true;
}


void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	ScrollBoxServerList->ClearChildren();

	uint32 idx = 0;
	for (const FString& ServerName : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		Row->ServerName->SetText(FText::FromString(ServerName));
		Row->Setup(this, idx);
		++idx;
		ScrollBoxServerList->AddChild(Row);
	}

}


void UMainMenu::SelectIndex(uint32 Index)
{
	// overload which is Set() + IsSet()
	SelectedIndex = Index;
}


void UMainMenu::BtnHostClicked()
{
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
	if(!ensure(JoinMenu!=nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if(!ensure(MenuInterface!=nullptr)) return;
	MenuInterface->RefreshServerList();
}


void UMainMenu::BtnBackClicked()
{
	if(!ensure(MenuSwitcher!=nullptr)) return;
	if(!ensure(StartMenu!=nullptr)) return;
	MenuSwitcher->SetActiveWidget(StartMenu);
}


void UMainMenu::BtnJoinClicked()
{
	if (SelectedIndex.IsSet() && MenuInterface!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index: %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Selected index not set!"));
	}
	
}


void UMainMenu::BtnQuitClicked()
{
	if(MenuInterface!=nullptr)
	{
		MenuInterface->QuitGame();
	}
}
