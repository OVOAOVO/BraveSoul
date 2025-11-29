// Created By -> OVOAOVO <- Copy Left

#include "Player/BSPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

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

void ABSPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    APawn* ControlledPawn = GetPawn<APawn>();
    USpringArmComponent* SpringArm = ControlledPawn->FindComponentByClass<USpringArmComponent>();
    UCameraComponent* cameraA = ControlledPawn->FindComponentByClass<UCameraComponent>();
    USceneCaptureComponent2D* SceneCaptureCompoent = ControlledPawn->FindComponentByClass<USceneCaptureComponent2D>();

    FVector WorldLocation = cameraA->GetComponentLocation();
    FVector RightVector = cameraA->GetRightVector();

    FRotator SpringArmWorldLocation = SpringArm->GetComponentRotation();
    FVector A = WorldLocation.RotateAngleAxis(SpringArmWorldLocation.Pitch, RightVector);
    FVector B = A.RotateAngleAxis(SpringArmWorldLocation.Yaw * (-1.f), ControlledPawn->GetActorUpVector());

    FVector SnappedLocation = B.GridSnap(SceneCaptureCompoent->OrthoWidth / SceneCaptureCompoent->TextureTarget->SizeX);

    FVector C = SnappedLocation.RotateAngleAxis(SpringArmWorldLocation.Yaw, ControlledPawn->GetActorUpVector());
    FVector D = C.RotateAngleAxis(SpringArmWorldLocation.Pitch * (-1.f), RightVector);


    SceneCaptureCompoent->SetWorldLocation(D, false, nullptr, ETeleportType::None);
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
            FRotator CurrentRot = SpringArm->GetComponentRotation();

            float NewYaw = CurrentRot.Yaw + InputAxisVector.X;
            float NewPitch = CurrentRot.Pitch + InputAxisVector.Y;

            NewPitch = FMath::Clamp(NewPitch, -80.f, 80.f);

            SpringArm->SetWorldRotation(FRotator(NewPitch, NewYaw, 0.f));

            FRotator NewControlRotation = GetControlRotation();
            NewControlRotation.Yaw = NewYaw;
            NewControlRotation.Pitch = NewPitch;
            SetControlRotation(NewControlRotation);
        }
    }
}