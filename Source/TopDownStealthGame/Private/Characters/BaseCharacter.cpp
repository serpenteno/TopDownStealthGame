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

	if (GetVelocity().Length() > GetCharacterMovement()->MaxWalkSpeedCrouched)
	{
		MovementState = EMovementState::Running;
	}
	else if (GetVelocity().Length() <= GetCharacterMovement()->MaxWalkSpeedCrouched && GetVelocity().Length() > 0.0f)
	{
		if (GetVelocity().Length() <= MaxCrawlSpeed && CharacterStance == ECharacterStance::Prone)
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

