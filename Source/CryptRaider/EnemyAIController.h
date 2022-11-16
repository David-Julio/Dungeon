// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds);

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* AIBehavior;
};
