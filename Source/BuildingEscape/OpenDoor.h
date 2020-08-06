// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void ClosedDoor(float DeltaTime);
	float TotalMassOfActors() const;	
	void FindAudioComponent();
	void FindpressurePlate();

	//tracks wether the sound is played. 
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;


private:
	float InitialYaw;
	float CurrentYaw;

	//Uproperty allows us to expose parameters on the Unreal UI	
	//forexample now the parameter Target yaw is available everywhere on the UI
		UPROPERTY(EditAnywhere); 
		float OpenAngle = 90.f;

		UPROPERTY(EditAnywhere); 
		ATriggerVolume* PressurePlate = nullptr;

		// UPROPERTY(EditAnywhere); 
		// AActor* ActorThatOpen;


		//values need to be initilized or will cause a crash
		float DoorLastOpened = 0.f;
		
		UPROPERTY(EditAnywhere); 
		float DoorCloseDelay = .5f;

		UPROPERTY(EditAnywhere); 
		float DoorOpenSpeed = .8f;

		UPROPERTY(EditAnywhere); 
		float DoorCloseSpeed = 2.f;
		
		UPROPERTY(EditAnywhere); 
		float MassToOpenDoors = 50.f;

		UPROPERTY();
		UAudioComponent* AudioComponent = nullptr;

};
