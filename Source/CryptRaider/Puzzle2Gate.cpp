// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle2Gate.h"
#include "Mover.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APuzzle2Gate::APuzzle2Gate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Mesh->SetupAttachment(Root);

	MoverComponent = CreateDefaultSubobject<UMover>(TEXT("Mover"));
	AddOwnedComponent(MoverComponent);
}

// Called when the game starts or when spawned
void APuzzle2Gate::BeginPlay()
{
	Super::BeginPlay();
	
	if (MoverComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover Component is added"));
	}
}

// Called every frame
void APuzzle2Gate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzle2Gate::SetShouldMoveInMoverComponent(bool ShouldMove)
{
	if (MoverComponent)
	{
		MoverComponent->SetShouldMove(ShouldMove);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Puzzle2Gate SetShouldMove not working"));
	}
}
