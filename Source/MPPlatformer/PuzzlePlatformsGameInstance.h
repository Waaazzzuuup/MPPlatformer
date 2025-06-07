#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"

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
	void Join(const FString& Address );

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	
};
