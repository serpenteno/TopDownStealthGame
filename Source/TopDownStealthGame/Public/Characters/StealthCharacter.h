// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "StealthCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

/**
 * Main character's class
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API AStealthCharacter final : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AStealthCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Callbacks for InputActions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SwitchView(const FInputActionValue& Value);
	void ChangeStance(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);

	bool CanMove() const;
	bool CanLook() const;

	// Enhanced Input
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> StealthMappingContext;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction> SwitchViewAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction> ChangeStanceAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction> AimAction;

	// Camera
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> TopDownCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	// Montages
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> StanceTransitionMontage;

};
