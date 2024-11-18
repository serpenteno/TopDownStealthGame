// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/StealthCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AStealthCharacter::AStealthCharacter()
{
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Top-Down Camera"));
	TopDownCamera->SetupAttachment(GetRootComponent());

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First-Person Camera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());

	MainCamera = TopDownCamera;
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
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStealthCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStealthCharacter::Look);
	}
}

void AStealthCharacter::Move(const FInputActionValue& Value)
{

}

void AStealthCharacter::Look(const FInputActionValue& Value)
{

}
