// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	float Reach = 100.f;
	UPROPERTY();
	UPhysicsHandleComponent* PhysicsHandle = nullptr;//will protect against random function
	UPROPERTY();
	UInputComponent* InputComponent = nullptr;
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();

	//returns the first actor within reach with a physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return The line Trace End 
	FVector GetPlayersReach() const;

	//Get Players Postion in the World
	FVector GetPlayersWorldPos() const;
};
