// Fill out your copyright notice in the Description page of Project Settings.

#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ABlasterCharacter::ABlasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct spring arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Attach springarm to the mesh
	CameraBoom->SetupAttachment(GetMesh());
	// Set the length of spring arm
	CameraBoom->TargetArmLength = 600.f;
	// Set spring arm to be rotated along with player controller when adding mouse input
	CameraBoom->bUsePawnControlRotation = true;

	// Construct camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach camera to the spring arm
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Set camera not to be rotated since it's attached to the spring arm
	FollowCamera->bUsePawnControlRotation = false;

	// Set sprint status
	bIsSprinting = false;
	// Set walk speed
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	// Set sprint speed (editable in editor)
	SprintSpeed = 800.f;

	// Set crouch speed (editable in editor)
	CrouchSpeed = 300.f;
}


// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABlasterCharacter::ControlYaw(const FInputActionValue &Value){
	AddControllerYawInput(Value.Get<float>());
}


void ABlasterCharacter::ControlPitch(const FInputActionValue &Value){
	AddControllerPitchInput(Value.Get<float>());
}


void ABlasterCharacter::MoveForward(const FInputActionValue &Value){
	// Get the forward vector from the controller's rotation
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// Get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// Apply movement
	AddMovementInput(Direction, Value.Get<float>());
}


void ABlasterCharacter::MoveRight(const FInputActionValue &Value){
	// Get the right vector from the controller's rotation
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// Get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// Apply movement
	AddMovementInput(Direction, Value.Get<float>());
}


void ABlasterCharacter::StartSprint(const FInputActionValue& Value)
{
	if (bIsCrouched){
		UnCrouch();
	}

	if (!bIsSprinting){
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}


void ABlasterCharacter::StopSprint(const FInputActionValue& Value){
    if (bIsSprinting){
        bIsSprinting = false;
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}


void ABlasterCharacter::StartCrouch(const FInputActionValue& Value){
    if (bIsSprinting){
        bIsSprinting = false;
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }

    Crouch();

    GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}


void ABlasterCharacter::StopCrouch(const FInputActionValue& Value){
    UnCrouch();

    if (bIsSprinting){
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
    else{
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}


void ABlasterCharacter::StartJump(const FInputActionValue& Value){
	if (bIsCrouched){
		UnCrouch();
	}

	Jump();
}


void ABlasterCharacter::StopJump(const FInputActionValue& Value){
    StopJumping();
}


// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Bind IMC(input mapping context)s */
	// Get PlayerController
	APlayerController *PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController){
		// Get EnhancedInputLocalPlayerSubsystem
		UEnhancedInputLocalPlayerSubsystem *EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (EnhancedInputLocalPlayerSubsystem){
			// Bind CameraInputMappingContext
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(CameraInputMappingContext, 0);
			// Bind MovementInputMappingContext
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(MovementInputMappingContext, 0);
		}
	}
	/* Bind IA(input action)s */
	// Get EnhancedInputComponent
	UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent){
		// Bind look actions
		EnhancedInputComponent->BindAction(ControlYawAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::ControlYaw);
		EnhancedInputComponent->BindAction(ControlPitchAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::ControlPitch);
		// Bind move actions
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::MoveRight);
        // Bind SprintAction
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::StartSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ABlasterCharacter::StopSprint);
		// Bind CrouchAction
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ABlasterCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ABlasterCharacter::StopCrouch);
		// Bind JumpAction
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABlasterCharacter::StopJump);
	}
}

