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
	float Speed = 100.0f;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	float PathLength;
	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
};
