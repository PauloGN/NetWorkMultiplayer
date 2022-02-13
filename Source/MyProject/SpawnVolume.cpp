// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include  "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

			FVector spawnLocation = GetRandomPointInVolume();

			//set a random rotation for the spawned pickup

			FRotator spawnRotation;

			spawnRotation.Yaw = FMath::FRand() * 360.0f;
			spawnRotation.Pitch = FMath::FRand() * 360.0f;
			spawnRotation.Roll = FMath::FRand() * 360.0f;

			//drop the new pickup into the world and get its reference

			APickup* spawnedPickup = world->SpawnActor<APickup>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);

		}

	}


}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

