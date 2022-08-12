//
//  WeaponSystemCharacter.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/WeaponSystemCharacter.h"

// Sets default values
AWeaponSystemCharacter::AWeaponSystemCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    if(!WeaponManagerComponent)
    {
        WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("Weapon Manager Component"));
        WeaponManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(WeaponManagerComponent);
    }
    
    if(!ScoreManagerComponent)
    {
        ScoreManagerComponent = CreateDefaultSubobject<UScoreManagerComponent>(TEXT("Score Manager Component"));
        ScoreManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(ScoreManagerComponent);
    }

    if(!MuzzlePosition)
    {
        MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleSceneComponent"));
        MuzzlePosition->SetupAttachment(RootComponent);
        MuzzlePosition->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
    }
}


AWeaponSystemCharacter::AWeaponSystemCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    
    if(!WeaponManagerComponent)
    {
        WeaponManagerComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponManagerComponent>(this, TEXT("Weapon Manager Component"));
        WeaponManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(WeaponManagerComponent);
    }
    
    if(!ScoreManagerComponent)
    {
        ScoreManagerComponent = ObjectInitializer.CreateDefaultSubobject<UScoreManagerComponent>(this, TEXT("Score Manager Component"));
        ScoreManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(ScoreManagerComponent);
    }

    if(!MuzzlePosition)
    {
        MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleSceneComponent"));
        MuzzlePosition->SetupAttachment(RootComponent);
        MuzzlePosition->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
    }
}

void AWeaponSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (PlayerInputComponent == nullptr) return;
    
    if(!WeaponManagerComponent)
    {
        UDbg::DbgMsg(FString("WeaponManagerComponent NOT SETUP (IS NULL)"));
    }
    else
    {
        WeaponManagerComponent->SetupPlayerInput(PlayerInputComponent, InputComponent);
    }
}

