// PolyShooter By DChepurkin

#include "Environments/PSVerticalDoor.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSVerticalDoor, All, All);

APSVerticalDoor::APSVerticalDoor()
{
	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorStaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	DoorStaticMesh->SetupAttachment(GetRootComponent());
}

void APSVerticalDoor::BeginPlay()
{
	Super::BeginPlay();

	check(DoorStaticMesh);

	ClosePosition = DoorStaticMesh->GetRelativeLocation();
	OpenPosition = FVector(ClosePosition.X, ClosePosition.Y, ClosePosition.Z + OpenDoorSpace);
}

void APSVerticalDoor::OnTimelineTick(float Alpha)
{
	Super::OnTimelineTick(Alpha);
	const auto CurrentPosition = FMath::Lerp(ClosePosition, OpenPosition, Alpha);
	DoorStaticMesh->SetRelativeLocation(CurrentPosition);
}
