#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"

#include "MainMenu.generated.h"

UCLASS()
class MPPLATFORMER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// we need to connect (create) the interface here 
	void SetMenuInterface(IMenuInterface* MI);

	void Setup();
	void Teardown();
	
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

	// switcher and menu widgets
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* StartMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* EditTextAddress;

	// button functions 
	UFUNCTION()
	void BtnHostClicked();

	UFUNCTION()
	void BtnOpenJoinMenuClicked();

	UFUNCTION()
	void BtnBackClicked();

	UFUNCTION()
	void BtnJoinClicked();
	
	// so menu class has an interface
	IMenuInterface* MenuInterface;
};
