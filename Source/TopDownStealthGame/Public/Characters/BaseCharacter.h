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
	Prone UMETA(DisplayName = "Prone"),
	Crouch UMETA(DisplayName = "Crouch"),
	Stand UMETA(DisplayName = "Stand")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECharacterStance CharacterStance = ECharacterStance::Stand;

};
