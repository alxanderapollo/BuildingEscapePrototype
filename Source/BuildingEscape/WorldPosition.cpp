// Fill out your copyright notice in the Description page of Project Settings.

//header file
#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
//construct world postion
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//when the game is initialized, everything in here will be run
// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//Fstrng class
	// FString Log = TEXT("Hello");
	// FString* PtrLog = &Log;//string ptr pointing to the log variable

	

	// PtrLog->Len(); //indirct poitning to the length of the varaible of log, Log.Len(); //print out the length 

	// //we have two asterisks, becasue we need to dereferenece, and overload the opertor
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);// yellow message
	//grey message
	//UE_LOG(LogTemp, Display, TEXT("Just a log, nothing to see!"));
	//red message
	//UE_LOG(LogTemp, Error, TEXT("Error"));//red message 

	// this peice of code returns the object names of the components laid on the world.
	FString objName = GetOwner()->GetName();//returns the name of the obj, cube and actor_1
	// FString* ptr = &objName;
	// UE_LOG(LogTemp, Warning, TEXT("object name is: %s"), **ptr);

	//this piece of code prints out the name and position of the componenets
	FString objectPosition = GetOwner()->GetActorLocation().ToString();//returns a FString
	UE_LOG(LogTemp, Warning, TEXT("%s Position in world  is: %s"), *objName,*objectPosition);



}



// Called every frame
//any code after the super tick componenet will be run every frame of the game
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

