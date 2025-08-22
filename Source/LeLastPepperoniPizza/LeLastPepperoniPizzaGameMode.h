// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LeLastPepperoniPizzaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LELASTPEPPERONIPIZZA_API ALeLastPepperoniPizzaGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);
protected:
	virtual void BeginPlay() override;

private:
	void RandomlySpawnEnemyInRadius();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Properties")
	float SpawnRadius = 400.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Properties")
	float SpawnInterval = 2.f;
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Properties")
	TSubclassOf<class APineapple> PineappleClass;

	class APineapple* Pineapple;
	class APizza* Pizza;
};
