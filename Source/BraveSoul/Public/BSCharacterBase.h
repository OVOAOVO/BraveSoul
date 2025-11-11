// Created By -> OVOAOVO <- Copy Left

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BSCharacterBase.generated.h"

UCLASS()
class BRAVESOUL_API ABSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABSCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
