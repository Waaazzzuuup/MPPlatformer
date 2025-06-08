#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "MenuWidget.generated.h"


UCLASS()
class MPPLATFORMER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// we need to connect (create) the interface here 
	void SetMenuInterface(IMenuInterface* MI);

	void Setup();
	void Teardown();

protected:
	// so menu class has an interface
	IMenuInterface* MenuInterface;
};
