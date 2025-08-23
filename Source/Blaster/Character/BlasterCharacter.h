// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "BlasterCharacter.generated.h"


UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlasterCharacter();

private:
	// Spring arm
	UPROPERTY(VisibleAnywhere, Category = "CameraComponents")
	class USpringArmComponent *CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, Category = "CameraComponents")
	class UCameraComponent *FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Camera IMC
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Camera")
	TObjectPtr<UInputMappingContext> CameraInputMappingContext;
	// Look IA
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Camera|Bases")
	TObjectPtr<UInputAction> ControlYawAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Camera|Bases")
	TObjectPtr<UInputAction> ControlPitchAction;

	// Movement IMC
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Movement")
	TObjectPtr<UInputMappingContext> MovementInputMappingContext;
	// Move IA
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Movement|Bases")
	TObjectPtr<UInputAction> MoveForwardAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "EnhancedInput|Movement|Bases")
	TObjectPtr<UInputAction> MoveRightAction;
	// Sprint IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput|Movement|Actions")
	TObjectPtr<UInputAction> SprintAction;
    // Crouch IA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput|Movement|Actions")
    TObjectPtr<class UInputAction> CrouchAction;
	// Jump IA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput|Movement|Actions")
	TObjectPtr<UInputAction> JumpAction;

private:
	// Walk Speed
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DefaultWalkSpeed = 600.f;
	// Sprint Speed
	bool bIsSprinting;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DefaultSprintSpeed = 900.f;
	// Crouch Speed
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DefaultCrouchSpeed = 300.f;

	// Helper function to update movement speed
	void UpdateMovementSpeed();

protected:
	// Look IA
	void ControlYaw(const FInputActionValue &Value);
	void ControlPitch(const FInputActionValue &Value);
	// Move IA
	void MoveForward(const FInputActionValue &Value);
	void MoveRight(const FInputActionValue &Value);
	// Sprint IA
	void StartSprint(const FInputActionValue &Value);
	void StopSprint(const FInputActionValue &Value);
	// Crouch IA
	void StartCrouch(const FInputActionValue &Value);
	void StopCrouch(const FInputActionValue &Value);
	// Jump IA
	void StartJump(const FInputActionValue &Value);
	void StopJump(const FInputActionValue &Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};