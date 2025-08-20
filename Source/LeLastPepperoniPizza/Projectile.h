// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class LELASTPEPPERONIPIZZA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	float Speed = 2000.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Combat")
	class UParticleSystem* HitParticle;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
