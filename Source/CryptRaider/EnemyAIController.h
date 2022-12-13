// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AWeapon;

UCLASS()
class CRYPTRAIDER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds);
	void Attack(bool IntentionToHit);
	void BeingAttacked();

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Axe;

	UPROPERTY(EditAnywhere)
	UAnimSequence* MyAnimSequence;

/*
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
 	class UBlendSpace1D* BlendSpace;
*/
	UPROPERTY(EditAnywhere)
	class UAnimationAsset* SwingAnimation;

	void SetBeingHitToFalse();
};
