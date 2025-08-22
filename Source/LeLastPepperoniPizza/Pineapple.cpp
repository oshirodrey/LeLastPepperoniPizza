// Fill out your copyright notice in the Description page of Project Settings.


#include "Pineapple.h"
#include "Pizza.h"
#include "Kismet/GameplayStatics.h"



void APineapple::BeginPlay()
{
	Super::BeginPlay();
	Pizza = Cast<APizza>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APineapple::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


void APineapple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttackThePizza();
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

