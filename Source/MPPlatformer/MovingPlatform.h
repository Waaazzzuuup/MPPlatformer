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

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true))
	FVector TargetLocation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 10.0f;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	float PathLength;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
};
