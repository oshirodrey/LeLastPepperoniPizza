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
		countEliminatedPineapples++;
        
	}
}

void ALeLastPepperoniPizzaGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn enemies every after set interval
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,
			this,
			&ALeLastPepperoniPizzaGameMode::RandomlySpawnEnemyInRadius,
			SpawnInterval,
			true);
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
