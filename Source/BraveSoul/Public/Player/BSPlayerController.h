// Created By -> OVOAOVO <- Copy Left

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class BRAVESOUL_API ABSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABSPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> BSInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RotationCameraAction;

	void Move(const FInputActionValue& InputActionValue);

	void RotationCamera(const FInputActionValue& InputActionValue);
};
