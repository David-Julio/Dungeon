// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleHoles.h"

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
	
}

// Called every frame
void APuzzleHoles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> APuzzleHoles::CheckIfActorsAreAcceptable(TArray<AActor*> OverlappingActors)
{
	
}

void APuzzleHoles::AcceptableActorTriggered()
{
	AmountInHole += 1;
}

