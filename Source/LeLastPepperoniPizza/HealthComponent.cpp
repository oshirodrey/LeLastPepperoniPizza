// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "LeLastPepperoniPizzaGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	ABasePawn* OwnerPawn = Cast<ABasePawn>(GetOwner());
	if (OwnerPawn)
	{
		MaxHealth = OwnerPawn->GetMaxHealth();
	}
	else
	{
		MaxHealth = 100.f;
	}
	CurrentHealth = MaxHealth;
	GameModeRef = Cast<ALeLastPepperoniPizzaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken); // Bind the damage event
	
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f|| CurrentHealth <= 0.f) return;
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);	if (CurrentHealth <=0 )
	{
		if (GameModeRef) GameModeRef->ActorDied(DamagedActor);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

