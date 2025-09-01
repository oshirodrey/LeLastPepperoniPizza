// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupTarget.h"
#include "Pizza.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerupTarget::APowerupTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void APowerupTarget::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->OnComponentHit.AddDynamic(this,&APowerupTarget::OnHit);

	BaseMesh->SetCollisionObjectType(ECC_GameTraceChannel1);


	Pizza = Cast<APizza>(UGameplayStatics::GetPlayerPawn(this, 0));
	BuffType = FMath::RandBool() ? EBuffType::RapidFire : EBuffType::InstantHeal;

}

void APowerupTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr || OtherActor == nullptr )
	{
		Destroy();
		return;
	}
	if (AProjectile * BulletHit = Cast<AProjectile>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerupTarget hit: Buff=%s, Duration=%.2f, Magnitude=%.2f, By=%s"),
									*StaticEnum<EBuffType>()->GetNameStringByValue(static_cast<int64>(BuffType)),
									Duration,
									Magnitude,
									*GetNameSafe(OtherActor));
		if (BuffType == EBuffType::RapidFire)
		{
			// If Magnitude > 0, use it as shots/sec; otherwise Pizza uses its RapidFireInterval
			// Pass Duration and Magnitude along
			
				
				Pizza->ApplyBuff(BuffType, Duration, Magnitude);
		}
		else
		{
			Pizza->ApplyBuff(BuffType, Duration, HealMagnitude);
		}
		Destroy();

	}
	
}

// Called every frame
void APowerupTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

