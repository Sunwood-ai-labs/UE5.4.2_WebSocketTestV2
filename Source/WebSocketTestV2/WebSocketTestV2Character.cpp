// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebSocketTestV2Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "WebSocketTestGameInstance.h"
#include "Misc/Char.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AWebSocketTestV2Character

AWebSocketTestV2Character::AWebSocketTestV2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AWebSocketTestV2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}


//////////////////////////////////////////////////////////////////////////
// NotifyServer
//
void AWebSocketTestV2Character::NotifyServer()
{
	UWebSocketTestGameInstance* GameInstance = Cast<UWebSocketTestGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		if (GameInstance->WebSocket->IsConnected())
		{
			GameInstance->WebSocket->Send("pressed E key");
		}
	}
}
void AWebSocketTestV2Character::StartNotifyServer()
{
	if (!bIsNotifying)
	{
		bIsNotifying = true;
		NotifyServer();
	}
}
void AWebSocketTestV2Character::EndNotifyServer()
{
	bIsNotifying = false;
}

//////////////////////////////////////////////////////////////////////////
// Hello
//
void AWebSocketTestV2Character::HelloServer()
{
	UWebSocketTestGameInstance* GameInstance = Cast<UWebSocketTestGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		if (GameInstance->WebSocket->IsConnected())
		{
			MessageUtf8 = u8"こんにちは";
			MessageUtf8Str = UTF8_TO_TCHAR(MessageUtf8);
			MessageJpTextLocal = StringCast<TCHAR>(*MessageUtf8Str);
			GameInstance->WebSocket->Send(MessageJpTextLocal);

		}
	}
}
void AWebSocketTestV2Character::StartHelloServer()
{
	if (!bIsHello)
	{
		bIsHello = true;
		HelloServer();
	}
}
void AWebSocketTestV2Character::EndHelloServer()
{
	bIsHello = false;
}

//////////////////////////////////////////////////////////////////////////
// Input
//
void AWebSocketTestV2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWebSocketTestV2Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWebSocketTestV2Character::Look);

		// Notify
		// EnhancedInputComponent->BindAction(NotifyAction, ETriggerEvent::Triggered, this, &AWebSocketTestV2Character::NotifyServer);
		EnhancedInputComponent->BindAction(NotifyAction, ETriggerEvent::Started, this, &AWebSocketTestV2Character::StartNotifyServer);
		EnhancedInputComponent->BindAction(NotifyAction, ETriggerEvent::Completed, this, &AWebSocketTestV2Character::EndNotifyServer);

		EnhancedInputComponent->BindAction(HelloAction, ETriggerEvent::Started, this, &AWebSocketTestV2Character::StartHelloServer);
		EnhancedInputComponent->BindAction(HelloAction, ETriggerEvent::Completed, this, &AWebSocketTestV2Character::EndHelloServer);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWebSocketTestV2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWebSocketTestV2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}