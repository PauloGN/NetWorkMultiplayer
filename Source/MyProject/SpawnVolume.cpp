// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include  "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{

		whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
		RootComponent = whereToSpawn;

		//set some bases values for range time
		spawnTimerLow = 1.0f;
		spawnTimerHigh = 5.0f;

	}

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	//set the timer to start spawning pickups
	SpawnDelay = FMath::FRandRange(spawnTimerLow, spawnTimerHigh);
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	
}

//Returns a random value within the bound box
FVector ASpawnVolume::GetRandomPointInVolume() const
{
	if (whereToSpawn)
	{
		const FVector spawnOrigin = whereToSpawn->Bounds.Origin;
		const FVector spawnExtend = whereToSpawn->Bounds.BoxExtent;

		return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtend);
	}


	return FVector();
}

void ASpawnVolume::SpawnPickup()
{

	// If we are the server and we have something to spawn

	if (GetLocalRole() == ROLE_Authority && IsValid(whatToSpawn))
	{
		//Check for Valid World
		if (UWorld* world = GetWorld())
		{
			// Set up any parameter/info
			FActorSpawnParameters spawnParams;

			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();

			//where shall we put the pick up

			const FVector spawnLocation = GetRandomPointInVolume();

			//set a random rotation for the spawned pickup

			FRotator spawnRotation;

			spawnRotation.Yaw = FMath::FRand() * 360.0f;
			spawnRotation.Pitch = FMath::FRand() * 360.0f;
			spawnRotation.Roll = FMath::FRand() * 360.0f;

			//drop the new pickup into the world and get its reference

			APickup* const spawnedPickup = world->SpawnActor<APickup>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);

			//Delay for a bit before spawning the next pickup
			SpawnDelay = FMath::FRandRange(spawnTimerLow, spawnTimerHigh);
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);

		}

	}


}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

