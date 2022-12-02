// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DetectCollisions();
}

void AWeapon::Attacked()
{
	IsHitting = true;
	//UE_LOG(LogTemp, Warning, TEXT("Attacked message from weapon"));
}

void AWeapon::DetectCollisions()
{
	GetOverlappingActors(OverlappingActorsArray);

	for (AActor* Actor : OverlappingActorsArray)
	{
		if (IsHitting && Actor->GetActorNameOrLabel() == "BP_Player")
		{
			AcceptableCollisionDetected();
		}
	}
}

void AWeapon::AcceptableCollisionDetected()
{
	UE_LOG(LogTemp, Warning, TEXT("Damage"));
	IsHitting = false;
}

