#pragma once

#include "Character/PSCharacterBase.h"

class PSUtils
{
public:
	static void PlayMontage(AActor* Actor, UAnimMontage* Montage)
	{
		const auto Character = Cast<APSCharacterBase>(Actor);
		if(!Montage ||
			!Character ||
			!Character->GetMainMesh() ||
			!Character->GetMainMesh()->GetAnimInstance())
			return;

		Character->GetMainMesh()->GetAnimInstance()->Montage_Play(Montage);
	}

	template <class T>
	static T* FindFirstNotify(const UAnimMontage* AnimMontage)
	{
		if(!AnimMontage) return nullptr;
		
		const auto& Notifies = AnimMontage->Notifies;
		for(const auto& NotifyEvent : Notifies)
		{
			if(const auto Notify = Cast<T>(NotifyEvent.Notify)) return Notify;
		}
		return nullptr;
	}
};
