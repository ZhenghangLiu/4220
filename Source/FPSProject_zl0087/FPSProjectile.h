// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_ZL0087_API AFPSProjectile : 
public AActor
{
	GENERATED_BODY()


public:
	/** Sphere collision component */
    UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
      USphereComponent* CollisionComp;
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	   UProjectileMovementComponent* ProjectileMovement;
	/** inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);

	AFPSProjectile(const FObjectInitializer& ObjectInitializer);


	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
