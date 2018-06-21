// Copyright Sean Duffy 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UECHARACTION_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	// Tracks noise used by pawn sense
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

public:
	// Sets default values for this character's properties
	ABaseCharacter(const class FObjectInitializer& ObjectInitializer);

	//Health
	UFUNCTION(BlueprintCallable, Category = "Condition")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Condition")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Condition")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsSprinting() const;

	virtual void SetSprinting(bool NewSprinting);

	float GetSprintingSpeedModifier() const;

	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Condition")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SprintingSpeedModifier;

	// Character wants to run, checked during Tick to see if allowed
	UPROPERTY()
	bool bWantsToRun;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent) const;

	virtual bool Die(float KillingDamage, FDamageEvent const& DamageEvent);

	virtual void OnDeath(float KillingDamage, FDamageEvent const& DamageEvent);

	void SetRagDollPhysics();

	bool bIsDying;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
