// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FPSProject_zl0087GameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_ZL0087_API AFPSProject_zl0087GameMode : public AGameMode
{
	GENERATED_BODY()
	
	
		virtual void StartPlay() override;
	AFPSProject_zl0087GameMode(
		const class FObjectInitializer& PCIP);


	
};
