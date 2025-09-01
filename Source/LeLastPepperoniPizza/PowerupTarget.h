// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffType.h"
#include "PowerupTarget.generated.h"

UCLASS()
class LELASTPEPPERONIPIZZA_API APowerupTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere) EBuffType BuffType;
	UPROPERTY(EditAnywhere) float Duration = 5.f;
	// For RapidFire, optional: treat Magnitude as shots‑per‑second (so interval = 1/Magnitude)
	UPROPERTY(EditAnywhere) float Magnitude = 0.2f;
	UPROPERTY(EditAnywhere) float HealMagnitude = 30.f;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	class APizza* Pizza; //Reference to the main target
};
