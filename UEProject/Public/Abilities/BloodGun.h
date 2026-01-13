#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeaponActor.h"
#include "BloodGun.generated.h"

class UEntityStats;

UCLASS(ClassGroup=(Weapons), Blueprintable)
class UEPROJECT_API ABloodGun : public ABaseWeaponActor
{
	GENERATED_BODY()

public:
	/** The bullet to spawn when shooting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<class ABloodGunBullet> BulletActor;

	/** The time between every shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float ShootCooldown = 0.2f;

	/** How long the bullets should live until they are destroyed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float BulletLifetime = 5.0f;

	/** The amount of bullets to shoot at max effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	int MaxEffectBulletAmount = 3;

	/** How long the player has to hold the button to get the maximum effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float MaxEffectInteractTime = 1.0f;

	/** Whether the owner should lose blood when shooting or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	bool bShouldTakeBlood = false;
	
	/** The amount of blood that will be consumed per shot if bShouldTakeBlood is true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float BloodCost = 5.0f;

	/** True when the character is shooting, used for animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsShooting = false;

protected:
	float InteractDuration = 0.0f;
	int BulletsToShoot = 0;
	double InteractionStartTime;

	UPROPERTY()
	TObjectPtr<AActor> M_Interactor;

	UPROPERTY()
	TObjectPtr<UEntityStats> InteractorEntityStats;

public:
	ABloodGun();
	
	void TriggerShoot();
	void FireBullet();
	
	void CalculateEffect(const float& InteractionDuration);

	virtual void InteractBegin(const TScriptInterface<IInteractor>& Interactor) override;
	virtual void InteractEnd(const TScriptInterface<IInteractor>& Interactor) override;
};