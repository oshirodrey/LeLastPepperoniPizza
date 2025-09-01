// Fill out your copyright notice in the Description page of Project Settings.


#include "Pizza.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BuffType.h"
#include "HealthComponent.h"
#include "Projectile.h"

APizza::APizza()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	PepperoniMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PepperoniMesh"));
	PepperoniMesh->SetupAttachment(BaseMesh);


}
// Called to bind functionality to input
void APizza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APizza::Shoot);

	

}

void APizza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		FVector HitLocation = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), HitLocation, 10, 10, FColor::Red, false, 0.0f);
		RotatePizza(HitLocation);
	}

	
}

void APizza::RotatePizza(FVector HitLocation)
{
	FVector ToTarget = HitLocation- BaseMesh->GetComponentLocation();
	FRotator Rotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	BaseMesh->SetWorldRotation(FMath::RInterpTo(
		BaseMesh->GetComponentRotation(),
		Rotation,
		GetWorld()->GetDeltaSeconds(),
		5.0f));
}//RInterpTo ensures smooth rotation
void APizza::ApplyBuff(EBuffType BuffType, float Duration, float Magnitude)
{
	switch (BuffType)
	{
	case EBuffType::RapidFire:
		StartRapidFire(Duration, Magnitude);
		break;

	case EBuffType::InstantHeal:
		if (UHealthComponent* HC = FindComponentByClass<UHealthComponent>())
		{
			const float Amount = (Magnitude != 0.f) ? Magnitude : 10.f;
			HC->AddHealth(Amount);
			UE_LOG(LogTemp, Warning, TEXT("Pizza does have HealthComponent when healing buff applied."));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pizza has no HealthComponent when healing buff applied."));
		}
		break;
	}
}

void APizza::StartRapidFire(float Duration, float Interval)
{
	// prevent stacking timers
	GetWorldTimerManager().ClearTimer(Timer_RapidFireExpire);
	GetWorldTimerManager().ClearTimer(Timer_RapidFireLoop);

	bRapidFireActive = true;
	

	// Looping timer to keep firing automatically
	GetWorldTimerManager().SetTimer(
		Timer_RapidFireLoop,
		this,
		&ThisClass::ShootOnceInstantly,
		Interval, 
		true);

	// Expire after Duration
	if (Duration > 0.f)
	{
		GetWorldTimerManager().SetTimer(
			Timer_RapidFireExpire,
			this,
			&ThisClass::StopRapidFire,
			Duration,
			false);
	}
}

void APizza::StopRapidFire()
{
	
	bRapidFireActive = false;
	GetWorldTimerManager().ClearTimer(Timer_RapidFireLoop);
	GetWorldTimerManager().ClearTimer(Timer_RapidFireExpire);
}

void APizza::HandleDestruction()
{
	Super::HandleDestruction();
	
}


void APizza::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void APizza::ShootOnceInstantly()
{
	if (ProjectileClass)
	{  	
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileClass,
				ProjectileSpawnPoint->GetComponentLocation(),
				ProjectileSpawnPoint->GetComponentRotation(),
				SpawnParams);
		
		// No need to call SetOwner manually anymore
	}
}


