// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"


class UBoxComponent;

UCLASS()
class MYPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Returns spawn volumes box components
	FORCEINLINE UBoxComponent* GetWhereToSpawn()const { return whereToSpawn;};

	// Find a random point within the box component
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//This is the pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> whatToSpawn;

	//Access to the timer for recurring spawning
	FTimerHandle spawnTimer;

	//Minimum spawn delay (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnTimerLow;

	//Maximum spawn delay (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnTimerHigh;

private:

	//Handle spawning new pick up
	void SpawnPickup();

	// Actual time (seconds) before spawning the next pickup
	float SpawnDelay;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The spawn area where pickups will be created
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* whereToSpawn;

};
