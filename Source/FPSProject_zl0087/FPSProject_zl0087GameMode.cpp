// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject_zl0087.h"
#include "FPSProject_zl0087GameMode.h"
#include "Engine.h"
#include "FPSHUD.h"

AFPSProject_zl0087GameMode::AFPSProject_zl0087GameMode(
	const class FObjectInitializer& PCIP) : Super(PCIP)
{
	HUDClass = AFPSHUD::StaticClass();
	// Creates a new blueprint object from the specified blueprint location
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/FPSContent/Blueprints/BP_FPSCharacter.BP_FPSCharacter'"));

	// If the object was created successfully, set the Blueprint object’s class to be used as our DefaultPawnClass (our in game character)
	if (PlayerPawnObject.Object != NULL)
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	
}

void AFPSProject_zl0087GameMode::StartPlay(){
	Super::StartPlay();
	StartMatch();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,
		FColor::Yellow, TEXT("HELLO WORLD"));
}
