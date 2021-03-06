// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject_zl0087.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"

AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create our CameraComponent
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	// Create a parent/child relationship between the Camera and the Capsule Bounding volume that surrounds your character. The parent is the Capsule
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	// Position the camera a bit above the eyes. BaseEyeHeight is an editable UPROPERTY and is shown in the screenshot below. Since our class derives Apawn this property is carried into FPSCharacter
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	// Allow the pawn to control rotation.
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true); // only the owning player will see this mesh
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent; // make the camera the parent object of this mesh
	FirstPersonMesh->bCastDynamicShadow = false; // mesh casts dynamic shadow
	FirstPersonMesh->CastShadow = false; // mesh casts shadow
	GetMesh()->SetOwnerNoSee(true); // everyone but the owner can see the regular body mesh

}


void AFPSCharacter::BeginPlay(){
	Super::BeginPlay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,
		FColor::Blue,
		TEXT("We are using FPSCharacter!"));
}

void AFPSCharacter::SetupPlayerInputComponent(
	UInputComponent* InputComponent)
{
	InputComponent->BindAxis("MoveForward", this,
		&AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this,
		&AFPSCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this,
		&AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this,
		&AFPSCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed,
		this, &AFPSCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released,
		this, &AFPSCharacter::OnStopJump);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
} // SetupPlayer

void AFPSCharacter::MoveForward(float Value){
	if ((Controller != NULL) && (Value != 0.0f)){
		//find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		//Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() ||
			GetCharacterMovement()->IsFalling())
			Rotation.Pitch = 0.0f;
		//add movement in that direction
		const FVector Direction =
			FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
} // Move forward

void AFPSCharacter::MoveRight(float Value){
	if ((Controller != NULL) && (Value != 0.0f)){
		//find out which way is right
		const FRotator Rotation =
			Controller->GetControlRotation();
		const FVector Direction =
			FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		//add movement in that direction
		AddMovementInput(Direction, Value);
	}
} // Move Right

void AFPSCharacter::OnStartJump(){
	bPressedJump = true;
}
void AFPSCharacter::OnStopJump(){
	bPressedJump = false;
}
void AFPSCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
	
			}
		}
	}
}