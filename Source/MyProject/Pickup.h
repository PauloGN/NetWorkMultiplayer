// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APickup : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	// Set default values
	APickup();

	// Required network scaffolding 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Return whether or not the pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive()const;

	// This allows the other classes to safely change the pickup's activation state
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetIsActive(bool newPickupStage);

protected:

	// True when the pick up can be used and false when the pickup is deactivated 
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	// This is called whenever bIsActive is updated
	UFUNCTION()
	virtual void OnRep_IsActive();


};
