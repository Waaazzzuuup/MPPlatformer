#include "PlatformTrigger.h"

#include "Components/BoxComponent.h"

#include "MovingPlatform.h"

APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume") );
	// new way to do early return type shit
	if (!ensure(TriggerVolume!=nullptr)) return;

	RootComponent = TriggerVolume;
}


void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	// can be moved to constructor, but constructor must be called
	// could not be called bc the map is loaded already (?)
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
	
}


void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activating trigger"));
	for(const auto Platform : ConnectedPlatforms)
	{
		Platform->AddActiveTrigger();		
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping trigger"));
	for(const auto Platform : ConnectedPlatforms)
	{
		Platform->RemoveActiveTrigger();		
	}
}

