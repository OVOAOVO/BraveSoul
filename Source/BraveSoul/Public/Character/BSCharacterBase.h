// Created By -> OVOAOVO <- Copy Left

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BSCharacterBase.generated.h"

UCLASS(Abstract)
class BRAVESOUL_API ABSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABSCharacterBase();

protected:
	virtual void BeginPlay() override;

};
