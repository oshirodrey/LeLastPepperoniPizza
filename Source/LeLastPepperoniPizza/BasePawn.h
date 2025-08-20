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

	
private:
	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass; // Class of the projectile to spawn



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetBulletSpeed() const { return BulletSpeed; }
	float GetBulletDamage() const { return BulletDamage; }



};
