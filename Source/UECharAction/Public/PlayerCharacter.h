// Copyright Sean Duffy 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class UECHARACTION_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:	
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

private:
	// ********** //
	// Components //
	// ********** //

	// Camera boom for player
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* CameraBoomComp;

	// Camera for player
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComp;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ******** //
	// Movement //
	// ******** //
	
	virtual void MoveForward(float Value);

	virtual void MoveRight(float Value);

	void OnStartJump();

	void OnStopJump();

	void OnStartSprinting();

	void OnStopSprinting();

	UPROPERTY()
	bool bIsJumping;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsInitiatedJump() const;

	void SetIsJumping(bool NewJump);

	void Landed(const FHitResult& Hit) override;

	void SetSprinting(bool NewSprinting);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprinting() const;

	float GetSprintSpeedModifier() const;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SprintSpeedModifier;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
