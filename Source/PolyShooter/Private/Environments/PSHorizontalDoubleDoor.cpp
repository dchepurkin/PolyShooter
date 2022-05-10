// PolyShooter By DChepurkin

#include "Environments/PSHorizontalDoubleDoor.h"

APSHorizontalDoubleDoor::APSHorizontalDoubleDoor()
{
	LeftDoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftDoorMesh");
	LeftDoorStaticMesh->SetupAttachment(GetRootComponent());

	RightDoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightDoorMesh");
	RightDoorStaticMesh->SetupAttachment(GetRootComponent());
}

void APSHorizontalDoubleDoor::BeginPlay()
{
	Super::BeginPlay();

	check(LeftDoorStaticMesh);
	check(RightDoorStaticMesh);

	LeftDoorClosePosition = LeftDoorStaticMesh->GetRelativeLocation();
	RightDoorClosePosition = RightDoorStaticMesh->GetRelativeLocation();
	LeftDoorOpenPosition = FVector(LeftDoorClosePosition.X + OpenDoorSpace, LeftDoorClosePosition.Y, LeftDoorClosePosition.Z);
	RightDoorOpenPosition = FVector(RightDoorClosePosition.X - OpenDoorSpace, RightDoorClosePosition.Y, RightDoorClosePosition.Z);
}

void APSHorizontalDoubleDoor::OnTimelineTick(float Alpha)
{
	Super::OnTimelineTick(Alpha);
	const auto LeftDoorCurrentPosition = FMath::Lerp(LeftDoorClosePosition, LeftDoorOpenPosition, Alpha);
	const auto RightDoorCurrentPosition = FMath::Lerp(RightDoorClosePosition, RightDoorOpenPosition, Alpha);

	LeftDoorStaticMesh->SetRelativeLocation(LeftDoorCurrentPosition);
	RightDoorStaticMesh->SetRelativeLocation(RightDoorCurrentPosition);
}
