// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaPlayerController.h"

void APizzaPlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
	bPlayerEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);
	bPlayerEnabled ? GetPawn()->SetActorHiddenInGame(!bPlayerEnabled): GetPawn()->SetActorHiddenInGame(!bPlayerEnabled);
	bShowMouseCursor = bPlayerEnabled;
}
