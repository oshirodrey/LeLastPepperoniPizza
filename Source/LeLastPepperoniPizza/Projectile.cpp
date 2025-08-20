// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h" // include for ABasePawn
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;

	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Retrieve speed from owner pawn once owner is valid
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit)	;

	if (const ABasePawn* OwnerPawn = Cast<ABasePawn>(GetOwner()))
	{
		Speed = OwnerPawn->GetBulletSpeed();
		ProjectileMovement->InitialSpeed = Speed;
		ProjectileMovement->MaxSpeed = Speed;

		// Ensure the movement component uses the new speed immediately
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovement->Activate(true);
	}

	// In AProjectile::BeginPlay or constructor
	ProjectileMesh->BodyInstance.bUseCCD = true;        // for UPrimitiveComponent* CollisionComp
	// and make sure it blocks the enemy channel:
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);


	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr || OtherActor == nullptr || OtherActor == MyOwner)
	{
		Destroy();
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageType = UDamageType::StaticClass();
	// Handle what happens when the projectile hits something
	if (OtherActor && OtherActor != MyOwner && OtherActor != this)
	{
		
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, MyOwnerInstigator, this, DamageType);
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *(OtherActor->GetName() + ""));
	}
	if (HitParticle) UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, Hit.ImpactPoint, FRotator(0.f, 0.f, 0.f));


	Destroy(); // Destroy the projectile after hitting

}