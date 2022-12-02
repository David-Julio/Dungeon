// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "AIController.h"


UBTTask_Attack::UBTTask_Attack()
{
    NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    /*
    FString Name = OwnerComp.GetAIOwner()->GetName();
    FString OwnerCompName = OwnerComp.GetName();
    FString OwnerCompOwnerName = OwnerComp.GetOwner()->GetName();

    AActor* OwnerCompOwner = OwnerComp.GetOwner();
    
    USceneComponent* RootComp = OwnerCompOwner->GetRootComponent();
    AController* Instagator = OwnerCompOwner->GetInstigatorController();
    APawn* OwnerPawn = Instagator->GetPawn();
    FString OwnerPawnName = OwnerPawn->GetActorNameOrLabel();

    OwnerPawn->GetActorNameOrLabel();
    //FString aicontrollerclassName = OwnerPawn->AIControllerClass->GetDisplayNameText().ToString();
    TSubclassOf<AController> AIControllerClass = OwnerPawn->AIControllerClass;
    //UObjectBase* AIBaseClass = AIControllerClass->GetClass();
    //FString aibaseclassName = AIBaseClass->GetFName().ToString();

    UClass* EnemyAIControllerRef = AIControllerClass->GetSuperClass();
    //EnemyAIController* EnemyAIControllerRefq = TSubClass<EnemyAIController> AIControllerClass->GetSuperClass();

    EnemyAIControllerRef->GetName();
    //FString EnemeyAIControllerName = EnemyAIControllerRef->GetName();
    //FString enemycontrollername = EnemyAIControllerRef->GetDefaultObjectName().ToString();

    //EnemyAIControllerRef->Attack();

    //UE_LOG(LogTemp, Error, TEXT("Object: %s OwnerComp: %s OwnerCompOwnerName: %s"), *Name, *OwnerCompName, *OwnerCompOwnerName);
    //UE_LOG(LogTemp, Warning, TEXT("ai controller class name: %s"), *enemycontrollername);

    AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
    FString AIActorName = AIActor->GetActorNameOrLabel();
    //AIActor->Attack();

    class EnemyAIController* EAIC = AIActor;

    UE_LOG(LogTemp, Warning, TEXT("AIActorName = %s"), *AIActorName);
    */

   //FString debugVar = OwnerComp.GetAIOwner()->GetPawn()->GetActorNameOrLabel();
   FString debugVar = OwnerComp.GetAIOwner()->GetInstigatorController()->GetActorNameOrLabel();
   AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()->GetInstigatorController());
   if (EnemyController == nullptr)
   {
        UE_LOG(LogTemp, Warning, TEXT("failed"));
        return EBTNodeResult::Failed;
   }
   EnemyController->Attack();
   
    return EBTNodeResult::Succeeded;
}
