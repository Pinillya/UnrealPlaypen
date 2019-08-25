// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

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

	//FQuat rotation = GetOwner()->GetTransform().GetRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Position of is at %f"), rotation.Z);
	GetOpenActor();
	
}

void UOpenDoor::GetOpenActor()
{
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenUpDoor()
{
	AActor* Owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, 50.f, 0.0f);
	Owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, 0.f, 0.0f);
	Owner->SetActorRotation(newRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && actorThatOpens && PressurePlate->IsOverlappingActor(actorThatOpens))
	{
		OpenUpDoor();
		countDown = DoorTimer;
	} else if (PressurePlate && chairThatOpens && PressurePlate->IsOverlappingActor(chairThatOpens)) {
		countDown = DoorTimer;
	} else {
		if (countDown == 1) {
			CloseDoor();
			countDown = 0;
		}

		if (countDown > 0) {
			countDown--;
		}
	}
}