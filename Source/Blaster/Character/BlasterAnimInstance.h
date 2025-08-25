// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "BlasterAnimInstance.generated.h"


UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance{
	GENERATED_BODY()

public:
	// Called at the very beginning of the game (much like BeginPlay function)
	virtual void NativeInitializeAnimation() override;
	// Called every frame (much like Tick function)
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	/* Variables to expose to animation bluprint */
	// Character
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true")) // Use this meta specifier to allow private access when using BlueprintReadOnly for private member
	class ABlasterCharacter *BlasterCharacter; // Foward declare the character pointer that is going to use the animation instance
	// Speed
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) // Use this meta specifier to allow private access when using BlueprintReadOnly for private member
	float Speed;
	// IsInAir
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) // Use this meta specifier to allow private access when using BlueprintReadOnly for private member
	bool bIsInAir;
	// IsAccelerating
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) // Use this meta specifier to allow private access when using BlueprintReadOnly for private member
	bool bIsAccelerating;
};
