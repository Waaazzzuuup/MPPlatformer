#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlatformTrigger.generated.h"

UCLASS()
class MPPLATFORMER_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class UBoxComponent* TriggerVolume; 

};
