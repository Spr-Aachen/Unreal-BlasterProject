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

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

