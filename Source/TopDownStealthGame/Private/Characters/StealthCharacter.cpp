// Copyright serpenteno, 2024. All Rights Reserved.


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
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Note: Should bones aren't refreshed, FirstPersonCamera does not follow the socket it is attached to during animations
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones; 

	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	bUseControllerRotationYaw = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = APlayerController::StaticClass();

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
		TopDownCamera->Activate();
		FirstPersonCamera->Deactivate();
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
	
		// Aim
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &AStealthCharacter::Aim);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &AStealthCharacter::Aim);
	}
}

void AStealthCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	CharacterStance = ECharacterStance::Crouching;
}

void AStealthCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	CharacterStance = ECharacterStance::Standing;
}

void AStealthCharacter::Move(const FInputActionValue& Value)
{
	if (CanMove())
	{
		const FVector2D Vector2DValue = Value.Get<FVector2D>();

		if (!bIsAiming)
		{
			const FRotator& CameraRotation = TopDownCamera->GetComponentRotation();
			const FRotator YawRotation = FRotator(0.0f, CameraRotation.Yaw, 0.0f);
			const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);
			const FVector& ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);
			const FVector& RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, Vector2DValue.Y);
			AddMovementInput(RightDirection, Vector2DValue.X);
		}
		else
		{
			const FRotator InputRotation = FVector(Vector2DValue.Y, Vector2DValue.X, 0.0f).Rotation();
			const FRotator TargetRotation = FRotator(0.0f, InputRotation.Yaw, 0.0f);
			const FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), AimingRotationSpeed);

			SetActorRotation(SmoothRotation);
		}
	}
}

void AStealthCharacter::Look(const FInputActionValue& Value)
{
	if (CanLook())
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

	const bool bValue = Value.Get<bool>();

	if (bValue)
	{
		// Ensure controller matches the FirstPersonCamera rotation
		if (GetController())
		{
			const FRotator& CameraRotation = FirstPersonCamera->GetComponentRotation();
			GetController()->SetControlRotation(FRotator(0.0f, CameraRotation.Yaw, 0.0f));
		}

		GetMesh()->SetOwnerNoSee(true);
		FirstPersonCamera->SetActive(true);
		TopDownCamera->SetActive(false);
		bUseControllerRotationYaw = true;
	}
	else
	{
		GetMesh()->SetOwnerNoSee(false);
		TopDownCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
		bUseControllerRotationYaw = false;
	}
}

void AStealthCharacter::ChangeStance(const FInputActionValue& Value)
{
	if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		const bool bValue = Value.Get<bool>();

		switch (CharacterStance)
		{
		case ECharacterStance::Standing:
			if (bValue)
			{
				// Prone();
			}
			else
			{
				Crouch();
			}
			break;

		case ECharacterStance::Crouching:
			if (bValue)
			{
				// Prone();
			}
			else
			{
				UnCrouch();
			}
			break;

		case ECharacterStance::Prone:
			if (bValue)
			{
				// UnProne();
			}
			else
			{
				// UnProne();
			}
			break;

		default:
			break;
		}
	}
}

void AStealthCharacter::Aim(const FInputActionValue& Value)
{
	const bool bValue = Value.Get<bool>();

	if (bValue)
	{
		bIsAiming = true;
	}
	else
	{
		bIsAiming = false;
	}
}

bool AStealthCharacter::CanMove() const
{
	return GetController() && TopDownCamera && TopDownCamera->IsActive() && !GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();
}

bool AStealthCharacter::CanLook() const
{
	return GetController() && FirstPersonCamera && FirstPersonCamera->IsActive();
}

