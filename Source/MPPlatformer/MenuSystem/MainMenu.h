#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "Blueprint/UserWidget.h"

#include "MainMenu.generated.h"

UCLASS()
class MPPLATFORMER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer );

	void SetServerList(TArray<FString> ServerNames);
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
	UButton* BtnBack;

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
	UWidget* StartMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ScrollBoxServerList;

	TSubclassOf<class UUserWidget> ServerRowClass;
	// might be a pointer, might be null
	TOptional<uint32> SelectedIndex;

	// button functions 
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
};
