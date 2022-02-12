// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Net/UnrealNetwork.h"


APickup::APickup()
{
	//Tell Ue4 to replicate this actor
	bReplicates = true;

	//disable event tick
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{
		bIsActive = true;
	}
	
}

void APickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickup, bIsActive);
}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetIsActive(bool newPickupStage)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		bIsActive = newPickupStage;
	}
}

void APickup::OnRep_IsActive()
{

}
