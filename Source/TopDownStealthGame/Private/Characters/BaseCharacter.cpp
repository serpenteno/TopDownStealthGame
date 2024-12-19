// Copyright © serpenteno, 2024. All Rights Reserved.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

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

