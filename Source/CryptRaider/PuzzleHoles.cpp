// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleHoles.h"
#include "Puzzle1ManagerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzleHoles::APuzzleHoles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleHoles::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Puzzle1Door"), AllPuzzle1Doors);
	Puzzle1Manager = AllPuzzle1Doors[0];

	Puzzle1ManagerComp = Puzzle1Manager->FindComponentByClass<UPuzzle1ManagerComponent>();
}

// Called every frame
void APuzzleHoles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AcceptableActorRef)
	{
		UpdateArray(AcceptableActorRef);
	}
}

void APuzzleHoles::CheckIfActorsAreAcceptable(TArray<AActor*> OverlappingActors)
{

	for (AActor* Actor : OverlappingActors)
    {
        bool HasAcceptableActorTag = Actor->ActorHasTag(AcceptableActorTag);
		
        if (HasAcceptableActorTag && !Puzzle1ManagerComp->AcceptableBallsInHoles.Contains(Actor))
        {
			AcceptableActorRef = Actor;
        }
		
    }
}

void APuzzleHoles::AcceptableActorTriggered()
{
	AmountInHole += 1;
}

void APuzzleHoles::UpdateArray(AActor* AcceptableActor)
{
	if (!Puzzle1ManagerComp->AcceptableBallsInHoles.Contains(AcceptableActor))
	{		
		Puzzle1ManagerComp->AcceptableBallsInHoles.Add(AcceptableActor);
	}
	if (Puzzle1ManagerComp->AcceptableBallsInHoles.Contains(AcceptableActor) && !IsOverlappingActor(AcceptableActor))
	{
		Puzzle1ManagerComp->AcceptableBallsInHoles.Remove(AcceptableActor);
		AcceptableActor = nullptr;
	}

}
