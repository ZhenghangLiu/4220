// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_ZL0087_API AFPSCharacter : 
public ACharacter
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	// FirstPersonMesh: 1st person view (arms; seen only by self)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FirstPersonMesh;

	// Specifies that the variable below can be seen in all Unreal Editor property windows, that the property can be read by Blueprints but not modified, and that the Category of the object is a Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		// Specifies a new first person camera component object
		UCameraComponent* FirstPersonCameraComponent;
	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;
	/** Gun muzzle's offset from the camera location */
	/** Projectile class to spawn */

protected:
	virtual void SetupPlayerInputComponent(
	class UInputComponent* InputComponent)
		override;
	UFUNCTION()
		void MoveForward(float Val);
	UFUNCTION()
		void MoveRight(float Val);
	//sets jump flag when key is pressed
	UFUNCTION()
		void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
		void OnStopJump();
	// Function that handles firing projectiles.
	//handles firing
	UFUNCTION()
		void OnFire();

	// A new constructor for the AFPSCharacter class
	AFPSCharacter(const FObjectInitializer& ObjectInitializer);
	
	
	
};
