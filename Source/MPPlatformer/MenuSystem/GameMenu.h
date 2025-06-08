#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "GameMenu.generated.h"


UCLASS()
class MPPLATFORMER_API UGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnBackToMainMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnCancel;

	// button functions 
	UFUNCTION()
	void BtnBackToMainMenuClicked();

	UFUNCTION()
	void BtnCancelClicked();
	
};
