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

	if(!ensure(BtnOpenHostMenu!=nullptr)) return false;
	BtnOpenHostMenu->OnClicked.AddDynamic(this, &UMainMenu::UMainMenu::BtnOpenHostMenuClicked);

	if(!ensure(BtnHost!=nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::BtnHostClicked);

	if(!ensure(BtnOpenJoinMenu!=nullptr)) return false;
	BtnOpenJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::BtnOpenJoinMenuClicked);

	if(!ensure(BtnBack!=nullptr)) return false;
	BtnBack->OnClicked.AddDynamic(this, &UMainMenu::BtnBackClicked);

	if(!ensure(BtnBack_1!=nullptr)) return false;
	BtnBack_1->OnClicked.AddDynamic(this, &UMainMenu::BtnBackClicked);
	
	if(!ensure(BtnJoin!=nullptr)) return false;
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::BtnJoinClicked);

	if(!ensure(BtnQuit!=nullptr)) return false;
	BtnQuit->OnClicked.AddDynamic(this, &UMainMenu::BtnQuitClicked);
	
	return true;
}


void UMainMenu::SetServerList(TArray<FServerData> ServerDataList)
{
	ScrollBoxServerList->ClearChildren();

	uint32 idx = 0;
	for (const FServerData& ServerData : ServerDataList)
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		Row->ServerName->SetText(FText::FromString(ServerData.ServerName));
		Row->UserName->SetText(FText::FromString(ServerData.UserName));
		FString NumPlayers = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->NumPlayers->SetText(FText::FromString(NumPlayers));
		Row->Setup(this, idx);
		++idx;
		ScrollBoxServerList->AddChild(Row);
	}

}


void UMainMenu::SelectIndex(uint32 Index)
{
	// overload which is Set() + IsSet()
	SelectedIndex = Index;
	UpdateChildrenRows();
}


void UMainMenu::UpdateChildrenRows()
{
	for (int32 i = 0; i < ScrollBoxServerList->GetChildrenCount(); i++)
	{
		auto Row = Cast<UServerRow>(ScrollBoxServerList->GetChildAt(i));
		if (Row!= nullptr) 
		{
			Row->IsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}


void UMainMenu::BtnOpenHostMenuClicked()
{
	if(!ensure(MenuSwitcher!=nullptr)) return;
	// can do it by index, but this is safer
	if(!ensure(HostMenu!=nullptr)) return;
	MenuSwitcher->SetActiveWidget(HostMenu);
	// if(!ensure(MenuInterface!=nullptr)) return;
	// MenuInterface->RefreshServerList();
}


void UMainMenu::BtnHostClicked()
{
	if(!ensure(HostNameEditText!=nullptr)) return;
	
	if(MenuInterface!=nullptr)
	{
		FString HostName = (HostNameEditText->GetText()).ToString();
		// call out a method on the interface
		// implementation is actually in GameInstance class
		MenuInterface->Host(HostName);
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
