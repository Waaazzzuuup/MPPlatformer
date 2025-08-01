// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MPPLATFORMER_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// equals zero IS pure virtual function (no implementation here, only in children)
	virtual void Host(FString ServerName) = 0;
	virtual void Join(uint32 Index) = 0;
	virtual void ReturnToMainMenu() = 0;
	virtual void QuitGame() = 0;
	virtual void RefreshServerList() = 0;
};
