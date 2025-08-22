// Fill out your copyright notice in the Description page of Project Settings.


#include "LeLastPepperoniPizzaGameMode.h"
#include "Pineapple.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void ALeLastPepperoniPizzaGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn enemies every after set interval
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,
			this,
			&ALeLastPepperoniPizzaGameMode::RandomlySpawnEnemyInRadius,
			SpawnInterval,
			true);
	
	
}

void ALeLastPepperoniPizzaGameMode::RandomlySpawnEnemyInRadius()
{
	float Angle = FMath::FRandRange(0, 2*PI);
	float XLocation = FMath::Cos(Angle) * SpawnRadius;
	float YLocation = FMath::Sin(Angle) * SpawnRadius;
	FVector SpawnLocation = FVector(XLocation, YLocation, 68);
	APineapple* NewPineapple = GetWorld()->SpawnActor<APineapple>(PineappleClass, SpawnLocation, FRotator(0, 0, 0));
	
	
	
}
