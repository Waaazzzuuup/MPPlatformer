#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"


UCLASS()
class MPPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	float PlatformSpeedX = 5.0f;

	UPROPERTY(EditAnywhere)
	float PlatformSpeedY = 0.0f;

	UPROPERTY(EditAnywhere)
	float PlatformSpeedZ = 0.0f;

protected:
	virtual void Tick(float DeltaTime) override;
	
};
