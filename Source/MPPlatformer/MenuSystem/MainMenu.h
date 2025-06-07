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
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnHost;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnJoin;

	UFUNCTION()
	void BtnHostClicked();

	UFUNCTION()
	void BtnJoinClicked();
	// so menu class has an interface
	IMenuInterface* MenuInterface;
	
};
