// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleHoles.generated.h"

UCLASS()
class CRYPTRAIDER_API APuzzleHoles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleHoles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> CheckIfActorsAreAcceptable(TArray<AActor*> OverlappingActors);
	void AcceptableActorTriggered();
	
private:
	int AmountInHole = 0;

	UPROPERTY(EditAnywhere)
	FString AcceptableTag;


};
