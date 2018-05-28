// Copyright Sean Duffy 2018

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->GravityScale = 1.5f;
	MoveComp->JumpZVelocity = 800;
	
	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComp->SocketOffset = FVector(0, 35, 0);
	CameraBoomComp->TargetOffset = FVector(0, 0, 55);
	CameraBoomComp->bUsePawnControlRotation = true;
	CameraBoomComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(GetRootComponent());

	SprintSpeedModifier = 2.5f;

	Health = 100.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWantsToRun && !IsSprinting())
	{
		SetSprinting(true);
	}

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("SprintHold", IE_Pressed, this, &APlayerCharacter::OnStartSprinting);
	PlayerInputComponent->BindAction("SprintHold", IE_Released, this, &APlayerCharacter::OnStopSprinting);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::OnStopJump);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::OnStartJump()
{
	bPressedJump = true;
	SetIsJumping(true);
}

void APlayerCharacter::OnStopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::OnStartSprinting()
{
	SetSprinting(true);
}

void APlayerCharacter::OnStopSprinting()
{
	SetSprinting(false);
}

bool APlayerCharacter::IsInitiatedJump() const
{
	return bIsJumping;
}

void APlayerCharacter::SetIsJumping(bool NewJump)
{
	bIsJumping = NewJump;
}

void APlayerCharacter::OnLanded(const FHitResult& Hit)
{
	Super::OnLanded(Hit);
	SetIsJumping(false);
}

void APlayerCharacter::SetSprinting(bool NewSprinting)
{
	bWantsToRun = NewSprinting;
}

bool APlayerCharacter::IsSprinting() const
{
	if (!GetCharacterMovement())
	{
		return false;
	}

	return bWantsToRun && !GetVelocity().IsZero();
}

float APlayerCharacter::GetSprintSpeedModifier() const
{
	return SprintSpeedModifier;
}

float APlayerCharacter::GetHealth() const
{
	return Health;
}

float APlayerCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<APlayerCharacter>()->Health;
}

bool APlayerCharacter::IsAlive() const
{
	return Health > 0.0f;
}

float APlayerCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return 0.0f;
	}

	const float RealDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (RealDamage > 0.0f)
	{
		Health -= RealDamage;
		if (Health <= 0)
		{
			//TODO Handled death
		}
		else
		{
			//TODO Play animation
		}
	}

	return RealDamage;
}

