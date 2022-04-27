// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PSAnimInstance.generated.h"

class APSCharacterBase;

UCLASS()
class POLYSHOOTER_API UPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category=PSAnimInstance)
	float Velocity = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category=PSAnimInstance)
	bool IsJump = false;
	
private:
	UPROPERTY()
	APSCharacterBase* Character;

	bool GetIsJump() const;
};
