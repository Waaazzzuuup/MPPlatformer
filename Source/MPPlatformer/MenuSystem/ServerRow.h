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
};
