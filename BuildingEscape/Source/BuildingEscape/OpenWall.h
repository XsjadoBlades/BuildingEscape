// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenWall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenWall : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenWall();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FWallEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FWallEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
		float TriggerMass = 70.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	//Returns total mass in kgs
	float GetTotalMassOfActorsOnPlate();
};
