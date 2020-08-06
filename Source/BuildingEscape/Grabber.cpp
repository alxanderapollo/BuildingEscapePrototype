// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


//define keyword 

#define OUT //makrs up our code we know that these are out params

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//only need it if in each frame we need to update something
	//in this case we do need it otherwise it may help improve perfromace
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}
void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		//UE_LOG(LogTemp, Warning, TEXT("Input Component found"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab",IE_Pressed, this,&UGrabber::Grab);
		InputComponent-> BindAction("Grab", IE_Released, this,&UGrabber::Release );
	}
	// else{
	// 	UE_LOG(LogTemp, Warning, TEXT("Input Component missing"), *GetOwner()->GetName());
	// }

}
void UGrabber:: FindPhysicsHandle(){
	//checking for Physics Handle Component
	PhysicsHandle = GetOwner() ->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle){
		//physics handle is found
		UE_LOG(LogTemp, Warning, TEXT("No Physics handle component found on: %s!"), *GetOwner()->GetName());
	}
	//UE_LOG(LogTemp,Warning, TEXT("Grabber Reporting for duty!"));

}
void UGrabber::Grab(){
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
	//TODO, only raycast when key is pressed and see if we reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit  = HitResult.GetActor();
	//try and reach any actor with a physics body collison channel set. 
	//if we hit something then attach the physics handle
	if(ActorHit){
		
		if(!PhysicsHandle){return;}
		//attatch physics handle 
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			GetPlayersReach()
		);
	
	}
}
FVector UGrabber:: GetPlayersReach() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
		//out does nothing for our code it is simply for readbility
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( 
	OUT PlayerViewPointLocation,
	OUT PlayerViewPointRotation);
	return   PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
void UGrabber::Release(){
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));
	if(!PhysicsHandle){return;}
	//remove relase physics handle
	PhysicsHandle ->ReleaseComponent();
}

FHitResult UGrabber:: GetFirstPhysicsBodyInReach() const{
		 //green line with 5 pixels in width, go out from the player 100 meters up
		// DrawDebugLine(
		// 	GetWorld(),
		// 	PlayerViewPointLocation,
		// 	LineTraceEnd,
		// 	FColor(0, 255, 0),
		// 	false,
		// 	0.f,
		// 	0,
		// 	5.f
		// ); 
		FHitResult Hit;
		//using ray cast for that, ra cast out to a certain distance(Reach)
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
		GetWorld()-> LineTraceSingleByObjectType(
			OUT Hit,
			GetPlayersWorldPos(),
			GetPlayersReach(),
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);

		return  Hit;
		// AActor* ActorHit = Hit.GetActor();
		
		// if(ActorHit){
		// 	UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit ->GetName()));
		// }
		// return Hit;
}
FVector UGrabber:: GetPlayersWorldPos() const{
		//1. getting the players VeiwPoint 
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		//out does nothing for our code it is simply for readbility
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( 
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);//out params

		//UE_LOG(LogTemp, Warning, TEXT("Location :%s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

		//Draw a line from player showing the reach 

		return PlayerViewPointLocation;

}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// if the phyic handle is attached 
	if(!PhysicsHandle){return;}
	if(PhysicsHandle->GrabbedComponent){
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}
		//move the object we are holding
	
	
	// ...
	//what we are tring to achive 
		
}
