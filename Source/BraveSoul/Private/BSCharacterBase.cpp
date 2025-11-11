// Created By -> OVOAOVO <- Copy Left


#include "BSCharacterBase.h"

// Sets default values
ABSCharacterBase::ABSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

