#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BloodGunBullet.generated.h"

class USphereComponent;

UCLASS()
class UEPROJECT_API ABloodGunBullet : public AActor
{
	GENERATED_BODY()

public:
	ABloodGunBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed = 1500.0f;

protected:
	virtual void BeginPlay() override;

	float BulletDamage = 2.0f;
	float BulletLifetime = 500.0f;
	float CurrentLifetime = 0.0f;

	UPROPERTY()
	TObjectPtr<AActor> BulletOwner;
	
public:
	void InitValues(const float Damage, const float Lifetime, const FVector& Direction, const TObjectPtr<AActor>& SomeOwner);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaSeconds) override;
};