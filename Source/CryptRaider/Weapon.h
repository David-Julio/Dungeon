// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CRYPTRAIDER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attacked(bool IntentionToHit);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	bool IsHitting = false;

	void DetectCollisions();

	TArray<AActor*> OverlappingActorsArray;

	void AcceptableCollisionDetected(AActor* ActorHit);

	UPROPERTY(EditAnywhere)
	float Damage = 25.f;
};
