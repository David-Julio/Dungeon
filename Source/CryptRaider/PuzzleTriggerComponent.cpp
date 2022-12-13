// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTriggerComponent.h"
#include "PuzzleHoles.h"

UPuzzleTriggerComponent::UPuzzleTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UPuzzleTriggerComponent::GetTriggeringActors()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    //APuzzleHoles PuzzleHolesReference = Cast<APuzzleHoles> ();
    GetOwner();
    /*
    if ()
    {

    }*/

    for (AActor* Actor : Actors)
    {
        bool HasAcceptableActorTag = Actor->ActorHasTag("Puzzle1");

        if (HasAcceptableActorTag)
        {
            return Actor;
        }
    }

    return nullptr;
}