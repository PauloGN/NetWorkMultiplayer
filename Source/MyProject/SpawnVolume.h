// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class MYPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns spawn volumes box components
	FORCEINLINE class UBoxComponent* GetWhereToSpawn()const { return whereToSpawn;};

	// Find a random point within the box component
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The spawn area where pickups will be created
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* whereToSpawn;

};
