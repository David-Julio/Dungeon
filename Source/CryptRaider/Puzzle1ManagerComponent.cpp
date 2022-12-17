// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle1ManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mover.h"

// Sets default values for this component's properties
UPuzzle1ManagerComponent::UPuzzle1ManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzle1ManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Puzzle1"), AllPuzzle1Balls);
}

void UPuzzle1ManagerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

// Called every frame
void UPuzzle1ManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%d"), AllPuzzle1Balls.Num());

	if (AllPuzzle1Balls.Num() == AcceptableBallsInHoles.Num())
	{
		if (Mover != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Working"));
			Mover->SetShouldMove(true);
		}
	}
}

