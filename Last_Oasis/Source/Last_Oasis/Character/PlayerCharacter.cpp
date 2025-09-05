// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/LOPlayerState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false;
    
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(
            TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Siru/Input/Input.Input'")
        );
    if (InputMappingContextRef.Object != nullptr)
    {
        InputMappingContext = InputMappingContextRef.Object;
    }
    
    // Attack
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_Attack.IA_Attack'")
    );
    if (InputActionAttackRef.Object != nullptr)
    {
        AttackAction = InputActionAttackRef.Object;
    }

    // Interaction
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInteractionRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_Interaction.IA_Interaction'")
    );
    if (InputActionInteractionRef.Object != nullptr)
    {
        Interaction = InputActionInteractionRef.Object;
    }

    // Jump
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_Jump.IA_Jump'")
    );
    if (InputActionJumpRef.Object != nullptr)
    {
        JumpAction = InputActionJumpRef.Object;
    }

    // Look
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_Look.IA_Look'")
    );
    if (InputActionLookRef.Object != nullptr)
    {
        LookAction = InputActionLookRef.Object;
    }

    // Move
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_Move.IA_Move'")
    );
    if (InputActionMoveRef.Object != nullptr)
    {
        MoveAction = InputActionMoveRef.Object;
    }

    // ToggleCraft
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionToggleCraftRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_ToggleCraft.IA_ToggleCraft'")
    );
    if (InputActionToggleCraftRef.Object != nullptr)
    {
        ToggleCraft = InputActionToggleCraftRef.Object;
    }

    // ToggleInventory
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionToggleInventoryRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_ToggleInventory.IA_ToggleInventory'")
    );
    if (InputActionToggleInventoryRef.Object != nullptr)
    {
        ToggleInventory = InputActionToggleInventoryRef.Object;
    }

    // ToggleMenu
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionToggleMenuRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_ToggleMenu.IA_ToggleMenu'")
    );
    if (InputActionToggleMenuRef.Object != nullptr)
    {
        ToggleMenu = InputActionToggleMenuRef.Object;
    }

    // ToggleMission
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionToggleMissionRef(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Siru/Input/IA_ToggleMission.IA_ToggleMission'")
    );
    if (InputActionToggleMissionRef.Object != nullptr)
    {
        ToggleMission = InputActionToggleMissionRef.Object;
    }
}

class UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void APlayerCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
    Super::FellOutOfWorld(dmgType);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
    if (ALOPlayerState* PS = GetPlayerState<ALOPlayerState>())
    {
        ASC = PS->GetAbilitySystemComponent();
        ASC ->InitAbilityActorInfo(PS,this);
    }
    APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
    PlayerController->ConsoleCommand(TEXT("Showdebug Abilitysystem"));
}

void APlayerCharacter::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    // Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }    
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
}

