// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MedievalInputConfig.h"
#include "EnhancedInputComponent.h"
#include "MedievalInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALMAYHEM_API UMedievalInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedPuncType, typename ReleasedFunctType, typename HeldFuncType>
	void BindAbilityActions(const UMedievalInputConfig* InputConfig, UserClass* Object, PressedPuncType PressedFunc, ReleasedFunctType ReleasedFunc, HeldFuncType HeldFunc);
};

template<class UserClass, typename PressedPuncType, typename ReleasedFunctType, typename HeldFuncType>
inline void UMedievalInputComponent::BindAbilityActions(const UMedievalInputConfig* InputConfig, UserClass* Object, PressedPuncType PressedFunc, ReleasedFunctType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for (const FMedievalInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
