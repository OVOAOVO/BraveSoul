// Created By -> OVOAOVO <- Copy Left


#include "Character/BSCharacterBase.h"

// Sets default values
ABSCharacterBase::ABSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}