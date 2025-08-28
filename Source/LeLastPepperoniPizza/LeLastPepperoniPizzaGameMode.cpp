// Fill out your copyright notice in the Description page of Project Settings.


#include "LeLastPepperoniPizzaGameMode.h"
#include "Pineapple.h"
#include "Pizza.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PizzaPlayerController.h"


void ALeLastPepperoniPizzaGameMode::ActorDied(AActor* DeadActor)
{
	// Handle the actor's death logic here
	if (DeadActor == Pizza)
	{
		if (PizzaPlayerController)
		{
			PizzaPlayerController->SetPlayerEnableState(false); // Disable player input
			Pizza->HandleDestruction();
			GameOver();
		}
       
	}
	else if (APineapple * DeadPineappleActor = Cast<APineapple>(DeadActor))
	{
		DeadPineappleActor->HandleDestruction();
		UpdateEnemyEliminated();
        
	}
}

void ALeLastPepperoniPizzaGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn enemies every after random intervals
	RescheduleSpawn();
	// Later I can make this game harder by set another timer to double this spawn schedule
	//...
	
	// Get the player's pizzapawn
	Pizza = Cast<APizza>(UGameplayStatics::GetPlayerPawn(this, 0));
	PizzaPlayerController = Cast<APizzaPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	
}


void ALeLastPepperoniPizzaGameMode::RandomlySpawnEnemyInRadius()
{
	float Angle = FMath::FRandRange(0, 2*PI);
	float XLocation = FMath::Cos(Angle) * SpawnRadius;
	float YLocation = FMath::Sin(Angle) * SpawnRadius;
	FVector SpawnLocation = FVector(XLocation, YLocation, 68);
	APineapple* NewPineapple = GetWorld()->SpawnActor<APineapple>(PineappleClass, SpawnLocation, FRotator(0, 0, 0));
	
	
	
}

void ALeLastPepperoniPizzaGameMode::RescheduleSpawn()
{
	float RandomInterval = FMath::FRandRange(SpawnIntervalMin , SpawnIntervalMax);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,
		this,
		&ALeLastPepperoniPizzaGameMode::SpawnEnemyAndReschedule,
		RandomInterval,
		true);
}

void ALeLastPepperoniPizzaGameMode::SpawnEnemyAndReschedule()
{
	RandomlySpawnEnemyInRadius();
	RescheduleSpawn();
}
