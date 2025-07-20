#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ServerRow.generated.h"

UCLASS()
class MPPLATFORMER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UserName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumPlayers;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* BackgroundButton;

	void Setup(class UMainMenu* NewParent, uint32 NewIndex);

	UPROPERTY(BlueprintReadOnly)
	bool IsSelected = false;

private:


	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;
	
	UFUNCTION()
	void BtnClicked();
	
};
