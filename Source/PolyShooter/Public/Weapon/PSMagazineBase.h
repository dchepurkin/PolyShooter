// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSMagazineBase.generated.h"

UCLASS()
class POLYSHOOTER_API APSMagazineBase : public AActor
{
	GENERATED_BODY()

public:
	APSMagazineBase();

	void SetMesh(UStaticMesh* NewMesh);
	void SetPhysicsEnabled(bool Enabled);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* Mesh;
};
