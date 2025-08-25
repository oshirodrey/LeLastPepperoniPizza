// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PizzaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LELASTPEPPERONIPIZZA_API APizzaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetPlayerEnableState(bool bPLayerEnabled);
};
