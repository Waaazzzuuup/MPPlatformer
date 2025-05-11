#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool IsServer = HasAuthority();
	if (IsServer)
	{
		FVector Location = GetActorLocation();
		Location += FVector(PlatformSpeedX,PlatformSpeedY,PlatformSpeedZ) * DeltaTime;
		SetActorLocation(Location);
	}
	
}


