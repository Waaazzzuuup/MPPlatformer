#include "PlatformTrigger.h"

#include "Components/BoxComponent.h"


APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName('TriggerVolume'));
	// new way to do early return type shit
	if (!ensure(TriggerVolume!=nullptr)) return;

	RootComponent = TriggerVolume;
	
}


void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}


void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

