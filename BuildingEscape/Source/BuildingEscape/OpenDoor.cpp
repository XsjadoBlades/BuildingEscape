// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OpenDoor()
{
	//Rotate the door to an open state
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	//Rotate the door to an open state
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	// If the ActorThatOpens is in the volume...
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		// ...Then open the door
		OpenDoor();
		DoorOpenTimeStamp = GetWorld()->GetTimeSeconds();
	}

	// Poll trigger volume every frame
	// If the time since the door was last opened is greater than the delay to close the door...
	if ((GetWorld()->GetRealTimeSeconds() - DoorOpenTimeStamp) > DoorCloseDelay)
	{
		// ...Then close the door
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Iterate through them adding their masses
	for(AActor* OverlappingActor : OverlappingActors)
	{
		//TotalMass += OverlappingActor->
	}

	return TotalMass;
}