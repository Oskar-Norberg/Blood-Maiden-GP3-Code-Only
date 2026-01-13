#include "Abilities/BloodGun.h"
#include "Abilities/BloodGunBullet.h"
#include "Entity/Components/Actor/EntityStats.h"

ABloodGun::ABloodGun()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ABloodGun::TriggerShoot()
{
	bIsShooting = true;
	
	FTimerHandle ShootCooldownTimer;
	GetWorld()->GetTimerManager().SetTimer(ShootCooldownTimer, this,
		&ABloodGun::FireBullet, ShootCooldown);
}

void ABloodGun::FireBullet()
{
	bIsShooting = false;
	
	BulletsToShoot -= 1;
	if(BulletsToShoot > 0)
	{
		TriggerShoot();
	}

	const FVector SpawnLocation = GetActorLocation();

	const TObjectPtr<AActor> Bullet = GetWorld()->SpawnActor(BulletActor, &SpawnLocation);
	const TObjectPtr<ABloodGunBullet> BulletCode = Cast<ABloodGunBullet>(Bullet);

	if(Bullet)
	{
		BulletCode->InitValues(AttackDamage, BulletLifetime,
			M_Interactor->GetActorForwardVector(), M_Interactor);
	}

	if (bShouldTakeBlood)
	{
		InteractorEntityStats->RemoveBlood(BloodCost);
	}
}

void ABloodGun::CalculateEffect(const float& InteractionDuration)
{
	//Crashes the program if the MaxEffectInteractTime is set to 0 or less
	checkf(MaxEffectInteractTime > 0.0f, TEXT("MaxEffectInteractionTime was <= 0, please ensure that it isn't!"));
	
	float EffectPercentage = InteractionDuration / MaxEffectInteractTime;
	
	if(EffectPercentage > 1.0f)
		EffectPercentage = 1.0f;

	const float PreciseBulletAmount = EffectPercentage * MaxEffectBulletAmount;
	
	int BulletAmount = FMath::RoundToInt(PreciseBulletAmount);

	if(BulletAmount < 1)
		BulletAmount = 1;

	BulletsToShoot = BulletAmount;
	
	FireBullet();
}

void ABloodGun::InteractBegin(const TScriptInterface<IInteractor>& Interactor)
{
	Super::InteractBegin(Interactor);

	InteractionStartTime = GetWorld()->GetTimeSeconds();
	
	M_Interactor = Cast<AActor>(Interactor.GetObject());
	InteractorEntityStats = Cast<UEntityStats>(M_Interactor->GetComponentByClass(UEntityStats::StaticClass()));
}

void ABloodGun::InteractEnd(const TScriptInterface<IInteractor>& Interactor)
{
	Super::InteractEnd(Interactor);

	InteractDuration = GetWorld()->GetTimeSeconds() - InteractionStartTime;

	CalculateEffect(InteractDuration);
}