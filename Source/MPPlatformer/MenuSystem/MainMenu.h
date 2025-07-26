#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"

#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()
	FString ServerName;
	FString UserName;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	
};


UCLASS()
class MPPLATFORMER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer );

	void SetServerList(TArray<FServerData> ServerDataList);
	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	// buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnHost;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnOpenJoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnOpenHostMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnBack;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnBack_1;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnJoin;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnQuit;

	// switcher and menu widgets
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* StartMenu;

	UPROPERTY(meta = (BindWidget))
	UEditableText* HostNameEditText;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ScrollBoxServerList;

	TSubclassOf<class UUserWidget> ServerRowClass;
	// might be a pointer, might be null
	TOptional<uint32> SelectedIndex;

	// button functions 
	UFUNCTION()
	void BtnOpenHostMenuClicked();

	UFUNCTION()
	void BtnHostClicked();

	UFUNCTION()
	void BtnOpenJoinMenuClicked();

	UFUNCTION()
	void BtnBackClicked();

	UFUNCTION()
	void BtnJoinClicked();

	UFUNCTION()
	void BtnQuitClicked();

	
	

	void UpdateChildrenRows();
};
