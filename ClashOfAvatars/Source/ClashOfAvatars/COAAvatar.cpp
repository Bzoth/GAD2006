// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

#include "IAutomationControllerManager.h"

ACOAAvatar :: ACOAAvatar()
{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->TargetArmLength = 300.0f;
	mSpringArm->SetupAttachment(RootComponent);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = true;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
}

// Called to bind functionality to input
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look",this,&ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACOAAvatar::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACOAAvatar::StopJump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);
}

void ACOAAvatar::RunPressed()
{
	if (!bStaminaDrained && Stamina > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bRunning = true;
	}
	
}

void ACOAAvatar::RunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bRunning = false;
}

void ACOAAvatar::StartJump()
{
	Jump();
}

void ACOAAvatar::StopJump()
{
	StopJumping();
}


void ACOAAvatar::MoveForward(float Value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection,Value);
}

void ACOAAvatar::MoveRight(float Value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection,Value);
}

void ACOAAvatar::CheckForStamina(float value)
{
	if ( value <= 0)
	{
		RunReleased();
		bStaminaDrained = true;
	}
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!bDead && GetCharacterMovement()->IsMovingOnGround())
	{
		if (bRunning)
		{
			Stamina = FMath::Clamp(FMath::Min(MaxStamina, Stamina - StaminaDrainRate * DeltaTime), 0.0f, MaxStamina);
			CheckForStamina(Stamina);
		}
		else if(GetCharacterMovement()->Velocity.Size() > 10.0f)
		{
			Stamina = FMath::Clamp(FMath::Min(MaxStamina, Stamina - StaminaDrainRate / 2 * DeltaTime), 0.0f, MaxStamina);
			CheckForStamina(Stamina);
		}
		else
		{
			Stamina = FMath::Clamp(FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime), 0.0f, MaxStamina);
			if (Stamina >= MaxStamina)
			{
				bStaminaDrained = false;
			}
		}
		
	}
	
}