// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include  "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

//Returns a random value within the bound box
FVector ASpawnVolume::GetRandomPointInVolume() const
{
	if (whereToSpawn)
	{
		FVector spawnOrigin = whereToSpawn->Bounds.Origin;
		FVector spawnExtend = whereToSpawn->Bounds.BoxExtent;

		return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtend);
	}


	return FVector();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

