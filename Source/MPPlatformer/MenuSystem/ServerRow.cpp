#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"


void UServerRow::Setup(UMainMenu* NewParent, uint32 NewIndex)
{
	Parent = NewParent;
	Index = NewIndex;
	if(!ensure(BackgroundButton!=nullptr)) return;
	BackgroundButton->OnClicked.AddDynamic(this, &UServerRow::BtnClicked);
}


void UServerRow::BtnClicked()
{
	if(!ensure(Parent!=nullptr)) return;
	Parent->SelectIndex(Index);
}
