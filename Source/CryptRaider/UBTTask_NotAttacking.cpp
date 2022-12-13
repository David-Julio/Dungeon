// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTask_NotAttacking.h"

#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "AIController.h"


UUBTTask_NotAttacking::UUBTTask_NotAttacking()
{
    NodeName = "NotAttacking";
}

EBTNodeResult::Type UUBTTask_NotAttacking::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

   AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()->GetInstigatorController());
   if (EnemyController == nullptr)
   {
        UE_LOG(LogTemp, Warning, TEXT("failed"));
        return EBTNodeResult::Failed;
   }

   EnemyController->Attack(false);
   
    return EBTNodeResult::Succeeded;
}

