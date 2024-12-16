// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
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
