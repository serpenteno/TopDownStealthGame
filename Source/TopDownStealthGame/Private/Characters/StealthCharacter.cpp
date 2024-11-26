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

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First-Person Camera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("Head"));
	FirstPersonCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	bUseControllerRotationYaw = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;

	bCanProne = true;
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

	// Camera setup
	if (TopDownCamera && FirstPersonCamera)
	{
		TopDownCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
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

		// SwitchView
		EnhancedInput->BindAction(SwitchViewAction, ETriggerEvent::Started, this, &AStealthCharacter::SwitchView);
		EnhancedInput->BindAction(SwitchViewAction, ETriggerEvent::Completed, this, &AStealthCharacter::SwitchView);

		// ChangeStance
		EnhancedInput->BindAction(ChangeStanceAction, ETriggerEvent::Triggered, this, &AStealthCharacter::ChangeStance);
		EnhancedInput->BindAction(ChangeStanceAction, ETriggerEvent::Canceled, this, &AStealthCharacter::ChangeStance);
	}
}

void AStealthCharacter::Move(const FInputActionValue& Value)
{
	if (GetController() && TopDownCamera && TopDownCamera->IsActive())
	{
		const FVector2D Vector2DValue = Value.Get<FVector2D>();

		FVector CameraForward = TopDownCamera->GetForwardVector();
		FVector CameraRight = TopDownCamera->GetRightVector();

		CameraForward.Z = 0;
		CameraRight.Z = 0;
		CameraForward.Normalize();
		CameraRight.Normalize();

		AddMovementInput(CameraForward, Vector2DValue.Y);
		AddMovementInput(CameraRight, Vector2DValue.X);
	}
}

void AStealthCharacter::Look(const FInputActionValue& Value)
{
	if (GetController() && FirstPersonCamera && FirstPersonCamera->IsActive())
	{
		const FVector2D Vector2DValue = Value.Get<FVector2D>();

		AddControllerYawInput(Vector2DValue.X);
		AddControllerPitchInput(Vector2DValue.Y);
	}
}

void AStealthCharacter::SwitchView(const FInputActionValue& Value)
{
	if (!TopDownCamera || !FirstPersonCamera)
	{
		return;
	}

	if (TopDownCamera->IsActive())
	{
		// Ensure controller matches the FirstPersonCamera rotation
		if (GetController())
		{
			const FRotator& CameraRotation = FirstPersonCamera->GetComponentRotation();
			GetController()->SetControlRotation(FRotator(0.0f, CameraRotation.Yaw, 0.0f));
		}

		FirstPersonCamera->SetActive(true);
		TopDownCamera->SetActive(false);
		GetMesh()->SetVisibility(false);
		bUseControllerRotationYaw = true;
	}
	else if (FirstPersonCamera->IsActive())
	{
		TopDownCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
		GetMesh()->SetVisibility(true);
		bUseControllerRotationYaw = false;
	}
}

void AStealthCharacter::ChangeStance(const FInputActionValue& Value)
{
	const bool bValue = Value.Get<bool>();

	switch (CharacterStance)
	{
	case ECharacterStance::Prone:
		if (bValue)
		{
			CharacterStance = ECharacterStance::Standing;
		}
		else
		{
			CharacterStance = ECharacterStance::Crouching;
		}
		break;

	case ECharacterStance::Crouching:
		if (bValue)
		{
			CharacterStance = ECharacterStance::Prone;
		}
		else
		{
			CharacterStance = ECharacterStance::Standing;
		}
		break;

	case ECharacterStance::Standing:
		if (bValue)
		{
			CharacterStance = ECharacterStance::Prone;
		}
		else
		{
			CharacterStance = ECharacterStance::Crouching;
		}
		break;

	default:
		break;
	}
}

