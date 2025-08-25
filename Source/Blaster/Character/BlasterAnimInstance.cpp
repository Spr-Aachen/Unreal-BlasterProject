// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"

#include "BlasterAnimInstance.h"
#include "BlasterCharacter.h"


void UBlasterAnimInstance::NativeInitializeAnimation(){
    Super::NativeInitializeAnimation();

    // Cast to character
    BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}


void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime){
    Super::NativeUpdateAnimation(DeltaTime);

    /* Cast to character in the first frame */
    if (BlasterCharacter == nullptr){
        BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
    }
    if (BlasterCharacter == nullptr){
        return;
    }

    /* Set speed */
    // Get velocity
    FVector Velocity = BlasterCharacter->GetVelocity();
    // Zero out Z velocity
    Velocity.Z = 0.f;
    // Get speed through size of the vector
    Speed = Velocity.Size();

    /* Set bIsInAir */
    bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();

    /* Get bIsAccelerating */
    bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false; // Using ternary operator
}
