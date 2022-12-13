// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PuzzleTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UPuzzleTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UPuzzleTriggerComponent();
	
private:
	AActor* GetTriggeringActors();
};
