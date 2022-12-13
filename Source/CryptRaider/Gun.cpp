// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EnemyAIController.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Owner pawn not set!"));
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;
	//TODO: LineTrace


	//DrawDebugPoint(GetWorld(), Location, 20, FColor::Red, true);

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel3);
	if (bSuccess)
	{
		//Hit.GetActor()->GetActorNameOrLabel();
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetActorNameOrLabel());
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);

		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		
		if (Hit.GetActor()->GetActorNameOrLabel() == "BP_EnemyCharacter")
		{
			//Hit.GetActor()->Attack();
			AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(Hit.GetActor()->GetInstigatorController());
			if (EnemyAI == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("nullptr"));
			}
			EnemyAI->BeingAttacked();
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

