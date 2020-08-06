// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


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
	//set initial yaw 

	//these are the params to open the door
	InitialYaw = GetOwner()->GetActorRotation().Yaw;//gets the current objects yaw, which will be the initial yaw
	CurrentYaw = InitialYaw;//our current postion is set eqaul to where the intial yaw starts
	OpenAngle += InitialYaw;
	FindpressurePlate();
	FindAudioComponent();
	//getting actor propertoes
	//ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	// want to log out 
	
}
void UOpenDoor::FindAudioComponent()  {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent){
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio Component!"), *GetOwner()->GetName());
	}
}
void UOpenDoor::FindpressurePlate(){
	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio Component!"), *GetOwner()->GetName());
	}
}


// Called every frame, and updated every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//only open the door if the pressure plate

	//is overlapping actor is
	//keep nully away
	if (TotalMassOfActors() > MassToOpenDoors){
		OpenDoor(DeltaTime);
		//Door last Opened  = when the door was oepend
		//using this to make a timer
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}else{
		//if the door has been open longer than x seconds
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay){
			ClosedDoor(DeltaTime);
		}
	}
}
	void UOpenDoor::OpenDoor(float DeltaTime){
		//test
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	//linear interpolation is a method of curve fitting using linear polynomials
	//to construct new data points within the range od discrete set of known data points
	//in video game dev, known as lerp is function that interpolates(inserts), within a range base on a 't' param
	//where 't' is typivally withn a range of [0,1], where zero is the left boundry starting postion, and 1 the final postion or can think of as 100%
	//unreal takes 3 params or t's for this function 
	//start, end, step
	//step determines the the speed, whcih is measured as a float  for each Frame Rate.
	//current yaw is set to 0, becasue the inital yaw is set to 0
	//target yaw is equal to 90 degress plus the initial which starts at 0
	//moving at 2% step speed
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle,DeltaTime * DoorOpenSpeed); //changing the last param to delta time 
	//to match speed of system running game
	//FRotator class is used for rotations 
	//here we make a instance whcih will be the door rotating
	//this function gets the door's rotation
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	//setting the Yaw of the door to the current yaw whcih is moving
	DoorRotation.Yaw = CurrentYaw;
	//finally we get the actor and setActor rotation to the door Rotation
	GetOwner()->SetActorRotation(DoorRotation);
	// ...
		CloseDoorSound = false;
		if(!AudioComponent){return;}

		if(!OpenDoorSound){
		AudioComponent->Play();
		OpenDoorSound = true;
		}
	}
	//closed door
	void UOpenDoor::ClosedDoor(float DeltaTime){
	//InitialYaw because we want the door to go back to what it was before the target degree was reached
		CurrentYaw = FMath::Lerp(CurrentYaw,InitialYaw,DeltaTime * DoorCloseSpeed); //changing the last param to delta time 
		FRotator DoorRotation = GetOwner()->GetActorRotation();
		DoorRotation.Yaw = CurrentYaw;
		GetOwner()->SetActorRotation(DoorRotation);
		
		OpenDoorSound = false;
		if(!AudioComponent){return;}

		if(!CloseDoorSound){
		AudioComponent->Play();
		CloseDoorSound = true;
		}
	}
	float UOpenDoor::TotalMassOfActors() const{
		float TotalMass = 0.f;

		//find all overlapping actors
		TArray<AActor*> OverLappingActors;

		//if(!PhysicsHandle){return TotalMass;}

		PressurePlate->GetOverlappingActors(OUT OverLappingActors);

		//add up their masses

		///find an actors mass in UE4
		for(AActor* Actor : OverLappingActors){
			TotalMass += TotalMass + Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			//check to see if mass is working 
			//UE_LOG(LogTemp, Warning, TEXT("%s is on the Pressure plate!"), *Actor->GetName());
		}
		return TotalMass;
	}





	//Open door
	 //FMath linear interpolation --open the door
	// float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	 //Frotators stores rotations*****
	// FRotator OpenDoor(0.f,OpenAngle,0.f);
	// OpenDoor.Yaw = FMath::Lerp(CurrentYaw,OpenAngle, 0.02f);//need a current yaw, target yaw, and a value between 0 and 1 
	 //Change Yaw value of OpenDoor
	
	// GetOwner()->SetActorRotation(OpenDoor);//set the rotation to open the door

	
	// FRotator CurrentRotation = GetOwner()->GetActorRotation(); //floating value 
	// CurrentRotation.Yaw = 90.f;
