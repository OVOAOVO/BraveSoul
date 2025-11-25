// Created By -> OVOAOVO <- Copy Left

#include "Player/BSPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABSPlayerController::ABSPlayerController()
{
}

void ABSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    check(BSInputMappingContext);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(BSInputMappingContext, 0);

    bShowMouseCursor = false;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
    InputModeData.SetHideCursorDuringCapture(true);
    SetInputMode(InputModeData);
}

void ABSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABSPlayerController::Move);
    EnhancedInputComponent->BindAction(RotationCameraAction, ETriggerEvent::Triggered, this, &ABSPlayerController::RotationCamera);
}

void ABSPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }
}

void ABSPlayerController::RotationCamera(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        USpringArmComponent* SpringArm = ControlledPawn->FindComponentByClass<USpringArmComponent>();
        if (SpringArm)
        {
            FRotator CurrentRot = SpringArm->GetRelativeRotation();
            float NewYaw = CurrentRot.Yaw + InputAxisVector.X;
            SpringArm->SetRelativeRotation(FRotator(CurrentRot.Pitch, NewYaw, 0.f));

            FRotator NewControlRotation = GetControlRotation();
            NewControlRotation.Yaw += InputAxisVector.X;
            SetControlRotation(NewControlRotation);
        }
    }
}
