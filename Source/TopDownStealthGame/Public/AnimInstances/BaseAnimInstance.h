// Copyright © serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;

enum class ECharacterStance : uint8;
enum class EMovementState : uint8;

/**
 * Base for any character animation instance
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABaseCharacter> BaseCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> BaseCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|States")
	ECharacterStance CharacterStance;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|States")
	EMovementState MovementState;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming;

};
