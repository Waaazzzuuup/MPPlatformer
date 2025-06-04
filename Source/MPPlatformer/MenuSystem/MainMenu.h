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
	void SetMenuInterface(IMenuInterface* MI);
	
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

	IMenuInterface* MenuInterface;
	
};
