// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityStats.generated.h"

UENUM(BlueprintType)
enum EDamageType
{
	Slash, Stab, Projectile
};

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttacked, float, DamageAmount,
	AController*, DamageInstigator, AActor*, DamageCauser, EDamageType, DamageType);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealed, float, HealAmount, AController*, HealInstigator, AActor*, HealCauser);

// TODO: Consider passing instigator and causer on death.
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBloodChanged, float, NewBloodValue);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBloodBoundsChanged, int, NewMinBlood, int, NewMaxBlood);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCanTakeDamageStatusChanged, bool, NewCanTakeDamage);

// TODO: Theres a lot of unused functions. Do with this information what you will.
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEPROJECT_API UEntityStats : public UActorComponent
{
	GENERATED_BODY()

	// Events
public:
	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnAttacked OnAttacked;

	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnHealed OnHealed;
	
	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnBloodChanged OnBloodChanged;

	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnBloodBoundsChanged OnBloodBoundsChanged;

	UPROPERTY(BlueprintAssignable, Category="Player Stats/Events")
	FOnCanTakeDamageStatusChanged OnCanTakeDamageChanged;

public:
	UEntityStats();

	/// 
	/// @param DamageAmount Amount of damage to apply.
	/// @param DamageInstigator The controller that caused the damage. Say a player or an AI. Can be nullptr if not applicable.
	/// @param DamageCauser The actual actor that caused the damage, like a bullet or weapon.
	/// @param DamageType The type of damage being applied, like a slash or stab. Used for VFX implementations.
	/// 
	UFUNCTION(BlueprintCallable)
	void Attack(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType);
	
	/// 
	/// @param HealAmount Amount of health to restore.
	/// @param HealInstigator The controller that caused the healing. Say a player or an AI. Can be nullptr if not applicable.
	/// @param HealCauser The actual actor that caused the healing, like a health pack or spell.
	///
	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount, AController* HealInstigator, AActor* HealCauser);

	///
	/// This will just kill the entity. Straight up.
	/// @param DamageInstigator Controller that caused death.
	/// @param DamageCauser Actor that caused death.
	UFUNCTION(BlueprintCallable)
	void Kill(AController* DamageInstigator, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable)
	void AddBlood(float Amount);
	UFUNCTION(BlueprintCallable)
	void RemoveBlood(float Amount);
	UFUNCTION(BlueprintCallable)
	void SetBlood(float Amount);
	UFUNCTION(BlueprintCallable)
	float GetCurrentBlood() const;


	UFUNCTION(BlueprintCallable)
	void AddMaxBlood(int Amount);
	UFUNCTION(BlueprintCallable)
	void RemoveMaxBlood(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetMaxBlood(int NewMaxBlood);
	UFUNCTION(BlueprintCallable)
	int GetMaxBlood() const;

	UFUNCTION(BlueprintCallable)
	void AddMinBlood(int Amount);
	UFUNCTION(BlueprintCallable)
	void RemoveMinBlood(int Amount);
	UFUNCTION(BlueprintCallable)
	void SetMinBlood(int NewMinBlood);
	UFUNCTION(BlueprintCallable)
	int GetMinBlood() const;

	UFUNCTION(BlueprintCallable)
	bool GetCanTakeDamage() const { return CanTakeDamage;} 
	UFUNCTION(BlueprintCallable)
	void SetCanTakeDamage(bool NewCanTakeDamage);

	UFUNCTION(BlueprintCallable)
	void NotifyDeath();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player Stats/Properties")
	int StartingBlood;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player Stats/Properties")
	int MinBlood;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player Stats/Properties")
	int MaxBlood;

	bool CanTakeDamage;
	UPROPERTY(VisibleAnywhere)
	float CurrentBlood;

	UPROPERTY()
	TObjectPtr<AActor> OwnerActor;

	void ClampBlood();

	void NotifyAttacked(float DamageAmount, AController* DamageInstigator, AActor* DamageCauser, EDamageType DamageType) const;
	void NotifyHealed(float HealAmount, AController* HealInstigator, AActor* HealCauser) const;
	void NotifyBloodChanged() const;
	void NotifyBloodBoundsChanged() const;
	void GetOwnerHierarchy();
	
private:
	bool IsDead;
};
