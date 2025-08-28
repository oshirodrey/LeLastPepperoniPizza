// Fill out your copyright notice in the Description page of Project Settings.


#include "Pineapple.h"
#include "Pizza.h"
#include "Kismet/GameplayStatics.h"



void APineapple::BeginPlay()
{
	Super::BeginPlay();
	Pizza = Cast<APizza>(UGameplayStatics::GetPlayerPawn(this, 0));
	BaseMesh->OnComponentHit.AddDynamic(this,&APineapple::OnHit);

}

void APineapple::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AController* InstigatorController = GetInstigatorController();
	UClass* DamageType = UDamageType::StaticClass();

	// Ignore self and null
	if (!OtherActor || OtherActor == this)
	{
		HandleDestruction();
		return;
	}

	// Allow the owner (this pineapple) to damage the pizza
	if (OtherActor == Pizza)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, InstigatorController, this, DamageType);
		UE_LOG(LogTemp, Warning, TEXT("Pineapple hit the Pizza: %s"), *OtherActor->GetName());
		HandleDestruction();
		return;
	}

	
	// Removed HitParticle usage due to missing symbol
	HandleDestruction(); // Destroy the projectile after hitting
}

void APineapple::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


void APineapple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAtPizza();
	AttackThePizza();
}


void APineapple::LookAtPizza()
{
	FVector ToTarget = Pizza->GetActorLocation() - this->GetActorLocation();
	FRotator Rotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	this->BaseMesh->SetWorldRotation(Rotation);//RInterpTo ensures smooth rotation
}

void APineapple::AttackThePizza()
{
	if (Pizza)
	{
		this->BaseMesh->SetWorldLocation(FMath::VInterpTo(this->BaseMesh->GetComponentLocation(),
			Pizza->GetActorLocation(),
			GetWorld()->GetDeltaSeconds(),
			0.8f), true);
	}
	
}

