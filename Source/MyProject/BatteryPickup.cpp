// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	//Keep movement synced from server to client

	SetReplicates(true);
	SetReplicateMovement(true);


	// This pickup is physics enabled and should move
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);


}