// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LELASTPEPPERONIPIZZA_API BuffType
{
public:
	BuffType();
	~BuffType();
};
UENUM(BlueprintType)
enum class EBuffType : uint8
{
	RapidFire    UMETA(DisplayName = "Rapid Fire"),
	InstantHeal  UMETA(DisplayName = "Heal")
};