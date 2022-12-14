//
//  ScoreManagerComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 12.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//


#include "Score/ScoreManagerComponent.h"

// Sets default values for this component's properties
UScoreManagerComponent::UScoreManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UScoreManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UScoreManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreManagerComponent::SetScore(float Value)
{
    Score = Value;

	AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
	{
		WeaponSystemHUD->InfoHUDWidget->Score = Score;
	}	
}

void UScoreManagerComponent::AddScore(float Value)
{
    SetScore(Score + Value);
}

void UScoreManagerComponent::ResetScore()
{
    SetScore(0.0f);
}