// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRaiderCharacter.h"
#include "CryptRaiderProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Puzzle2Gate.h"


//////////////////////////////////////////////////////////////////////////
// ACryptRaiderCharacter

ACryptRaiderCharacter::ACryptRaiderCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void ACryptRaiderCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Gun setup
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
	Gun->SetOwner(this);

	// temp puzzle 2 setup -- not yet optimised
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Puzzle2"), Puzzle2ActorsArray);
	if (Puzzle2ActorsArray.Num() > 0)
	{
		Puzzle2Actor = Puzzle2ActorsArray[0];
		MoverActor = Cast<APuzzle2Gate>(Puzzle2Actor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No actor with 'Puzzle2' tag"));
	}

}

void ACryptRaiderCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (Mesh1P->GetAnimationMode() == EAnimationMode::AnimationSingleNode && !Mesh1P->IsPlaying())
    {
        Mesh1P->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    }
}

//////////////////////////////////////////////////////////////////////////// Input

void ACryptRaiderCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ACryptRaiderCharacter::OnPrimaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACryptRaiderCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACryptRaiderCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ACryptRaiderCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ACryptRaiderCharacter::LookUpAtRate);

	// Bind shooting events
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ACryptRaiderCharacter::Shoot);

	// Bind interact events
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Repeat, this, &ACryptRaiderCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Released, this, &ACryptRaiderCharacter::InteractRelease);
}

void ACryptRaiderCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void ACryptRaiderCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ACryptRaiderCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ACryptRaiderCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACryptRaiderCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACryptRaiderCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACryptRaiderCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool ACryptRaiderCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACryptRaiderCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ACryptRaiderCharacter::EndTouch);

		return true;
	}
	
	return false;
}

void ACryptRaiderCharacter::Shoot()
{
	Gun->PullTrigger();
	
    if (ShootAnimation)
    {
        Mesh1P->PlayAnimation(ShootAnimation, false);
        Mesh1P->IsPlaying();
        Mesh1P->GetAnimationMode();
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
    }
}

void ACryptRaiderCharacter::Interact()
{
	FVector Location;
	FRotator Rotation;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(Location, Rotation);
	

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel4);

	if (Puzzle2Actor != nullptr && bSuccess)
	{
		if (MoverActor != nullptr)
		{
			MoverActor->SetShouldMoveInMoverComponent(true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MoverActor Not pointing to anything"));
		}
	}
	else if (!bSuccess)
	{
		MoverActor->SetShouldMoveInMoverComponent(false);
	}
}

void ACryptRaiderCharacter::InteractRelease()
{
	if (Puzzle2Actor != nullptr)
	{
		MoverActor = Cast<APuzzle2Gate>(Puzzle2Actor);
		if (MoverActor != nullptr)
		{
			MoverActor->SetShouldMoveInMoverComponent(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MoverActor Not pointing to anything"));
		}
	}
}