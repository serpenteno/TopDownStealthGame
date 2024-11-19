// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StealthCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AStealthCharacter::AStealthCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Top-Down Camera"));
	TopDownCamera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AStealthCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (StealthMappingContext)
			{
				Subsystem->AddMappingContext(StealthMappingContext, 0);
			}
		}
	}
}

void AStealthCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStealthCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStealthCharacter::Move);

		// Look
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStealthCharacter::Look);
	}
}

void AStealthCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	FVector CameraForward = TopDownCamera->GetForwardVector();
	FVector CameraRight = TopDownCamera->GetRightVector();

	CameraForward.Z = 0;
	CameraRight.Z = 0;
	CameraForward.Normalize();
	CameraRight.Normalize();

	AddMovementInput(CameraForward, MoveValue.Y);
	AddMovementInput(CameraRight, MoveValue.X);
}

void AStealthCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}

