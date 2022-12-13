// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	/*
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	*/
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);
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

	//UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( IsHitting ? TEXT("true") : TEXT("false") ));

	if (IsHitting == true)
	{
		DetectCollisions();
	}
}

void AWeapon::Attacked(bool IntentionToHit)
{
	IsHitting = IntentionToHit;
}

void AWeapon::DetectCollisions()
{
	GetOverlappingActors(OverlappingActorsArray);

	for (AActor* Actor : OverlappingActorsArray)
	{
		if (Actor->GetActorNameOrLabel() == "BP_FirstPersonCharacter")
		{
			AcceptableCollisionDetected(Actor);
		}
	}
}

void AWeapon::AcceptableCollisionDetected(AActor* ActorHit)
{
	ActorHit->TakeDamage(Damage, FDamageEvent::FDamageEvent(), GetInstigatorController(), this);
	IsHitting = false;
}

