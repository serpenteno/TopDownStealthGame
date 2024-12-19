// Copyright © serpenteno, 2024. All Rights Reserved.


#include "Animations/BaseAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner()))
	{
		BaseCharacterMovement = BaseCharacter->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BaseCharacter && BaseCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(BaseCharacterMovement->Velocity);
		CharacterStance = BaseCharacter->GetCharacterStance();
		MovementState = BaseCharacter->GetMovementState();
		bIsAiming = BaseCharacter->GetIsAiming();
	}
}
