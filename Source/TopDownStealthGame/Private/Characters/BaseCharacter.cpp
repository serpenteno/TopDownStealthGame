// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector VelocityXY = GetVelocity();
	VelocityXY.Z = 0;
	const float& GroundSpeed = VelocityXY.Length();

	if (GroundSpeed > GetCharacterMovement()->MaxWalkSpeedCrouched)
	{
		MovementState = EMovementState::Running;
	}
	else if (GroundSpeed <= GetCharacterMovement()->MaxWalkSpeedCrouched && GroundSpeed > 0.0f)
	{
		if (GroundSpeed <= MaxCrawlSpeed && CharacterStance == ECharacterStance::Prone)
		{
			MovementState = EMovementState::Crawling;
		} 
		else
		{
			MovementState = EMovementState::Walking;
		}
	}
	else
	{
		MovementState = EMovementState::Idle;
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::PlayMontage(UAnimMontage* MontageToPlay, const FName& SectionName) const
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && MontageToPlay)
	{
		AnimInstance->Montage_Play(MontageToPlay);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

