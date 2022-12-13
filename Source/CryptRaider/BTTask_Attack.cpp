// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "AIController.h"


UBTTask_Attack::UBTTask_Attack()
{
    NodeName = "Attacking";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

   //FString debugVar = OwnerComp.GetAIOwner()->GetInstigatorController()->GetActorNameOrLabel();
   AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()->GetInstigatorController());
   if (EnemyController == nullptr)
   {
        UE_LOG(LogTemp, Warning, TEXT("failed"));
        return EBTNodeResult::Failed;
   }
   
   EnemyController->Attack(true);
   
    return EBTNodeResult::Succeeded;
}