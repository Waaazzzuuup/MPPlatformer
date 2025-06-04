#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "MainMenu.generated.h"

UCLASS()
class MPPLATFORMER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

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


	
};
