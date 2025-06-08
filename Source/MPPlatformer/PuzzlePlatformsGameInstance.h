#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"


#include "PuzzlePlatformsGameInstance.generated.h"

// gotta inherit it from an interface to use it (create an implementation)
UCLASS()
class MPPLATFORMER_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformsGameInstance( const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	// this is now an override function from the interface
	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address ) override;

	UFUNCTION(Exec)
	void ReturnToMainMenu() override;

	UFUNCTION(Exec)
	void TestConsole();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> GameMenuClass;
	class UMainMenu* Menu;
	class UGameMenu* GameMenu;
	
};
