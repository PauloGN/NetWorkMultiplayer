// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include  "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{

		whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
		RootComponent = whereToSpawn;

	}

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

