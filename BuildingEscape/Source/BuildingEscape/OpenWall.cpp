// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenWall.h"
#include "Gameframework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenWall::UOpenWall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenWall::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UOpenWall::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	// If the total mass on the plate is greater than or equal to the TriggerMass...
	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
	{
		// ...Then open the door
		OnOpen.Broadcast();
	}
	else
	{
		// ...close the door
		OnClose.Broadcast();
	}
}

float UOpenWall::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	///Iterate through them adding their masses
	for (auto& OverlappingActor : OverlappingActors)
	{
		//UE_LOG(LogTemp, Error, TEXT("Overlapping mass found - %s"), *OverlappingActor->GetName());
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Error, TEXT("Total mass on plate = %f"), TotalMass);

	return TotalMass;
}