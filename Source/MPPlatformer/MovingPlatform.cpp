#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		PathLength = (GlobalTargetLocation - GlobalStartLocation).Size();
	}
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
		
			float PathTravelled = (GlobalStartLocation - Location).Size();
			if (PathTravelled >= PathLength)
			{
				FVector tmp = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = tmp;
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Direction * Speed * DeltaTime;
			SetActorLocation(Location);
		}
	}
	
}


void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}


void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) ActiveTriggers--;
}



