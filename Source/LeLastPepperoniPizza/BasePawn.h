// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class LELASTPEPPERONIPIZZA_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	float GetMaxHealth() const { return MaxHealth; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* Capsule;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class USceneComponent* ProjectileSpawnPoint;
	
	void Shoot();

	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	float BulletSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	float BulletDamage = 10.0f;

	void HandleDestruction();
	
private:
	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass; // Class of the projectile to spawn

	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	float MaxHealth = 30.f;

	float CoolDown = 0.5f;
	
	bool IsCoolingDown = false;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetBulletSpeed() const { return BulletSpeed; }
	float GetBulletDamage() const { return BulletDamage; }



};
