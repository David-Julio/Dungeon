// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardClass.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardClass::UBTTask_ClearBlackboardClass()
{
    NodeName = TEXT("Clear Blackbourd Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardClass::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
