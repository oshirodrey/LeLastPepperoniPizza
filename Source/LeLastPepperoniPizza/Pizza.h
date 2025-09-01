// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Pizza.generated.h"

/**
 * 
 */
UCLASS()
class LELASTPEPPERONIPIZZA_API APizza : public ABasePawn
{
	GENERATED_BODY()
public:
	APizza();
	void HandleDestruction();
	UFUNCTION(BlueprintCallable)
	void ApplyBuff(EBuffType BuffType, float Duration = 5.f, float Magnitude = 0.f);

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RotatePizza(FVector HitLocation);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Component")
	class UStaticMeshComponent* PepperoniMesh;
	

	APlayerController* PlayerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Properties")
	float TurnRate = 100.f;
protected:
	
	

	FTimerHandle Timer_RapidFireExpire;
	FTimerHandle Timer_RapidFireLoop;


	bool bRapidFireActive = false;
	
	
	// Your normal fire function (called by input)
	UFUNCTION(BlueprintCallable) void ShootOnceInstantly();

	// Called by pickups:
	

	void StartRapidFire(float Duration, float Interval);
	void StopRapidFire();
};
