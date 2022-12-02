// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Animation/SkeletalMeshActor.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
    }
    

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    
    ACharacter* CharacterReference = Cast<ACharacter>(GetPawn());

    if (CharacterReference == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No Character Reference in EnemyAIController"));
    }

    Axe = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
    if (Axe == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("AWeapn 'Axe' is a nullptr"));
    }
    
    Axe->AttachToComponent(CharacterReference->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Axe->SetOwner(this);

    USkeletalMeshComponent* Mesh = GetPawn()->FindComponentByClass<USkeletalMeshComponent>();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    float PlayerLocationasdf = GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation")).X;

    if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }

    USkeletalMeshComponent* Mesh = GetPawn()->FindComponentByClass<USkeletalMeshComponent>();

    if (Mesh->GetAnimationMode() == EAnimationMode::AnimationSingleNode && !Mesh->IsPlaying())
    {
        Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    }
}

void AEnemyAIController::Attack()
{
    //UE_LOG(LogTemp, Display, TEXT("%s"), *GetPawn()->GetActorNameOrLabel());

    /*
    USkeletalMeshComponent* Mesh = GetPawn()->FindComponentByClass<USkeletalMeshComponent>();

    
    if (Mesh != nullptr)
    {
        UAnimInstance* AnimInst = Mesh->GetAnimInstance();
        if (AnimInst != nullptr)
        {
            if (MyAnimSequence != nullptr)
            {
                UE_LOG(LogTemp, Display, TEXT("throw"));
                AnimInst->PlaySlotAnimationAsDynamicMontage(MyAnimSequence, TEXT("Enemy_Swiping"), 0.1f, 0.1f, 1.0f, 30.0f);
            }
        }
    }*/

    /*
    ASkeletalMeshActor *Skel = Cast<ASkeletalMeshActor>(GetPawn());
    if (Skel)
    {
        USkeletalMeshComponent *Mesh = Skel->GetSkeletalMeshComponent();
        if (Mesh)
        {
            Mesh->PlayAnimation(BlendSpace, true);
            FVector BlendParams(50.0f, 0.0f, 0.0f);
            Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
        }

    }*/

    USkeletalMeshComponent* Mesh = GetPawn()->FindComponentByClass<USkeletalMeshComponent>();

    if (SwingAnimation)
    {
        

        Mesh->PlayAnimation(SwingAnimation, false);
        Mesh->IsPlaying();
        Mesh->GetAnimationMode();

    }

    Axe->Attacked();
}
