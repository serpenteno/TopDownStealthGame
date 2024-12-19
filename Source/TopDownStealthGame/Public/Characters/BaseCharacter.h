// Copyright © serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

/**
 * Describes the stance of a character
 */
UENUM(BlueprintType)
enum class ECharacterStance : uint8
{
	Standing UMETA(DisplayName = "Standing"),
	Crouching UMETA(DisplayName = "Crouching"),
	Prone UMETA(DisplayName = "Prone")
};

/**
 * Describes the movement of a character based on it's current speed
 */
UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Crawling UMETA(DisplayName = "Crawling"),
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running")
};

/**
 * The base for any game character
 */
UCLASS(Abstract)
class TOPDOWNSTEALTHGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void PlayMontage(UAnimMontage* MontageToPlay, const FName& SectionName) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States")
	ECharacterStance CharacterStance = ECharacterStance::Standing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	EMovementState MovementState = EMovementState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxCrawlSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanProne = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere)
	float AimingRotationSpeed = 10.0f;

public:
	FORCEINLINE ECharacterStance GetCharacterStance() const { return CharacterStance; }
	FORCEINLINE EMovementState GetMovementState() const { return MovementState; }
	FORCEINLINE bool GetIsAiming() const { return bIsAiming; }

};
