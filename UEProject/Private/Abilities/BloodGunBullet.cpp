#include "Abilities/BloodGunBullet.h"
#include "Components/SphereComponent.h"
#include "Entity/Components/Actor/EntityStats.h"

ABloodGunBullet::ABloodGunBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));

	//CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	//CollisionComponent->SetCollisionResponseToChannels(ECR_Overlap);
	//CollisionComponent->InitSphereRadius(5.0f);
	//RootComponent = CollisionComponent;

	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABloodGunBullet::OnOverlapBegin);
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->InitialSpeed = BulletSpeed;
	MovementComponent->MaxSpeed = BulletSpeed;
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->bShouldBounce = false;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->bRotationFollowsVelocity = true;
}

void ABloodGunBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABloodGunBullet::InitValues(const float Damage, const float Lifetime, const FVector& Direction, const TObjectPtr<AActor>& SomeOwner)
{
	BulletDamage = Damage;
	BulletLifetime = Lifetime;
	BulletOwner = SomeOwner;
	
	if(MovementComponent)
	{
		MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
	}
}

void ABloodGunBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!BulletOwner)
		return;
	
	if(OtherActor->ActorHasTag("Player") && BulletOwner->ActorHasTag("Player"))
		return;

	if(OtherActor->ActorHasTag("Enemy") && BulletOwner->ActorHasTag("Enemy"))
		return;

	//TODO: VFX and SFX
	//Implement bullet hit sound effect
	//Implement bullet hit visual effect
	//Give back blood to the actor that shot the bullet (done through the enemy itself?)

	const TObjectPtr<UActorComponent> EntityStats = OtherActor->GetComponentByClass(UEntityStats::StaticClass());
	if(!EntityStats)
		return;

	const TObjectPtr<UEntityStats> EntityStatsCode = Cast<UEntityStats>(EntityStats);
		
	if(EntityStats)
		EntityStatsCode->Attack(BulletDamage, BulletOwner->GetInstigatorController(), this, Projectile);
	
	if(OtherActor)
		Destroy();
}

void ABloodGunBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentLifetime += DeltaSeconds;

	if(CurrentLifetime >= BulletLifetime)
		Destroy();
}