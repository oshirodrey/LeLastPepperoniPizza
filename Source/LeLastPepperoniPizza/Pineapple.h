// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Pineapple.generated.h"

/**
 * 
 */
UCLASS()
class LELASTPEPPERONIPIZZA_API APineapple : public ABasePawn
{
	GENERATED_BODY()
private:
	class APizza* Pizza; //Reference to the main target
	
protected:
	void AttackThePizza();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void HandleDestruction();

	
};
