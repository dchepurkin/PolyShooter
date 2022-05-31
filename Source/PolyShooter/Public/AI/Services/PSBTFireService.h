// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PSBTFireService.generated.h"

class UPSWeaponComponent;

UCLASS()
class POLYSHOOTER_API UPSBTFireService : public UBTService
{
	GENERATED_BODY()

public:
	UPSBTFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSFireService)
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSFireService, meta=(ClampMin = "0.1"))
	float FireTime = 0.7f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSFireService, meta=(ClampMin = "100.0"))
	float FireDistance = 2000.0f;

private:
	FTimerHandle StopFireTimerHandle;
	
	void StopFire(UBehaviorTreeComponent* OwnerComp);
	UPSWeaponComponent* GetWeaponComponent(UBehaviorTreeComponent* OwnerComp);
	bool IsDistanceReadyToFire(UBlackboardComponent* Blackboard);
	bool IsPlayerVisible(UBehaviorTreeComponent* OwnerComp);
};
