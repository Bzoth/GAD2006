// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter() :
	bDead(false),
	Health(100.0f),
	MaxHealth(100.0f),
	HealingRate(1.0f),
	WalkSpeed(500.0f),
	RunSpeed(1000.0f),
	Stamina(100.0f),
	MaxStamina(100.0f),
	StaminaGainRate(10.0f),
	StaminaDrainRate(20.0f),
	bStaminaDrained(false),
	bRunning(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// Called when the game starts or when spawned
void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead)
	{
		Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
	}

}



