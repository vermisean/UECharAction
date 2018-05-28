// Copyright Sean Duffy 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class UECHARACTION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

private:
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

	UPROPERTY(Transient, Replicated)
	bool bWantsToRun;

	UPROPERTY(Transient, Replicated)
	bool bIsJumping;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsInitiatedJump() const;

	void SetIsJumping(bool NewJump);

	void OnLanded(const FHitResult& Hit) override;

	void SetSprinting(bool NewSprinting);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprinting() const;

	float GetSprintSpeedModifier() const;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SprintSpeedModifier;


	// ******** //
	//  Health  //
	// ******** //

	UFUNCTION(BlueprintCallable, Category = "Player Setup")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player Setup")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player Setup")
	bool IsAlive() const;

	UPROPERTY(EditDefaultsOnly, Category = "Player Setup")
	float Health;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
