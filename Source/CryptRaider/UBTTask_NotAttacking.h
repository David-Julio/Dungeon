// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_NotAttacking.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UUBTTask_NotAttacking : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UUBTTask_NotAttacking();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
