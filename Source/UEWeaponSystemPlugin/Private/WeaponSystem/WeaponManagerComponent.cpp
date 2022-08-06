//
//  WeaponManagerComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/WeaponManagerComponent.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    if(WeaponDefinitions)
    {
        WeaponDefinitions->RowStruct = FWeaponDefinition::StaticStruct();
    }
    
    if(!WeaponComponent)
    {
        WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));
        WeaponComponent->bEditableWhenInherited = true;
        WeaponComponent->RegisterComponent();
//        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP"));
    }
}

UWeaponManagerComponent::UWeaponManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    
    if(WeaponDefinitions)
    {
        WeaponDefinitions->RowStruct = FWeaponDefinition::StaticStruct();
    }
    
    if(!WeaponComponent)
    {
        WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponComponent>(this, TEXT("Weapon Component"));
        WeaponComponent->bEditableWhenInherited = true;
//        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP (ObjectInitializer)"));
        WeaponComponent->RegisterComponent();
    }
}

void UWeaponManagerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponManagerComponent::SetupPlayerInput(class UInputComponent* PlayerInputComponent, class UInputComponent* InputComponent)
{
    FInputKeyBinding KBP_PrimaryShootKey(FInputChord(PrimaryShootKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_PrimaryShootKey.bConsumeInput = true;
    KBP_PrimaryShootKey.bExecuteWhenPaused = false;

    KBP_PrimaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        WeaponComponent->StartShooting();
    });
    PlayerInputComponent->KeyBindings.Add(KBP_PrimaryShootKey);
    
    FInputKeyBinding KBR_PrimaryShootKey(FInputChord(PrimaryShootKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_PrimaryShootKey.bConsumeInput = true;
    KBR_PrimaryShootKey.bExecuteWhenPaused = false;
    KBR_PrimaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        WeaponComponent->StopShooting();
    });
    InputComponent->KeyBindings.Add(KBR_PrimaryShootKey);
    
    FInputKeyBinding KBP_SecondaryShootKey(FInputChord(SecondaryShootKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_SecondaryShootKey.bConsumeInput = true;
    KBP_SecondaryShootKey.bExecuteWhenPaused = false;

    KBP_SecondaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        WeaponComponent->StartShooting(EWeaponFunction::Secondary);
    });
    PlayerInputComponent->KeyBindings.Add(KBP_SecondaryShootKey);
    
    FInputKeyBinding KBR_SecondaryShootKey(FInputChord(SecondaryShootKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_SecondaryShootKey.bConsumeInput = true;
    KBR_SecondaryShootKey.bExecuteWhenPaused = false;
    KBR_SecondaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        WeaponComponent->StopShooting();
    });
    InputComponent->KeyBindings.Add(KBR_SecondaryShootKey);
    
    // AlternateCrosshairKey
    FInputKeyBinding KBP_AlternateCrosshairKey(FInputChord(AlternateCrosshairKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_AlternateCrosshairKey.bConsumeInput = true;
    KBP_AlternateCrosshairKey.bExecuteWhenPaused = false;

    KBP_AlternateCrosshairKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        UDbg::DbgMsg(FString("AlternateCrosshairKey PRESSED"));
        //WeaponComponent->StartShooting(EWeaponFunction::Secondary);
    });
    PlayerInputComponent->KeyBindings.Add(KBP_AlternateCrosshairKey);
    
    FInputKeyBinding KBR_AlternateCrosshairKey(FInputChord(AlternateCrosshairKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_AlternateCrosshairKey.bConsumeInput = true;
    KBR_AlternateCrosshairKey.bExecuteWhenPaused = false;
    KBR_AlternateCrosshairKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        UDbg::DbgMsg(FString("AlternateCrosshairKey RELEASED"));
        //WeaponComponent->StopShooting();
    });
    InputComponent->KeyBindings.Add(KBR_AlternateCrosshairKey);
    
    
    TArray<FName> RowNames = WeaponDefinitions->GetRowNames();
    int32 idx = 0;
    for ( auto& RowName : RowNames )
    {
        FWeaponDefinition* WeaponDefinition = WeaponDefinitions->FindRow<FWeaponDefinition>(RowName, "");
        if(WeaponDefinition)
        {
            FInputKeyBinding KBP(FInputChord(WeaponDefinition->ActivationKey, false, false, false, false), EInputEvent::IE_Pressed);
            KBP.bConsumeInput = true;
            KBP.bExecuteWhenPaused = false;
            KBP.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
            {
                WeaponComponent->SetCurrentWeapon(*WeaponDefinition);
            });
            PlayerInputComponent->KeyBindings.Add(KBP);
            if(idx == 0)
            {
                WeaponComponent->SetCurrentWeapon(*WeaponDefinition);
            }
            idx++;
        }
    }
}
