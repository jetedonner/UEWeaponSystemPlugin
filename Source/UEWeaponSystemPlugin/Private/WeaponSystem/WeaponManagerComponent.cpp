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
    
//    if(WeaponComponentNG)
//    {
//        UDbg::DbgMsg(FString("INITIALIZING WeaponComponentNG"));
////        TSubclassOf<class UWeaponComponentBase> It = WeaponManagerComponent->WeaponsArray[i];
////
////        if(It->IsChildOf(UWeaponComponentBase::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
////        {
////            if(It->GetClass() != UWeaponComponentBase::StaticClass() && !It->GetName().StartsWith(TEXT("SKEL_")))
////            {
////                UWeaponComponentBase* SpawnedWeapon = NewObject<UWeaponComponentBase>(WeaponManagerComponent->GetOwner(), It->GetDefaultObject()->GetClass());
////
//        WeaponComponent = NewObject<UWeaponComponent>(this, WeaponComponentNG->GetDefaultObject()->GetClass());
//        WeaponComponent->bEditableWhenInherited = true;
//        WeaponComponent->RegisterComponent();
////        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP"));
//    }
//    else
//    {
//        UDbg::DbgMsg(FString("NOOOOOOOOT INITIALIZING WeaponComponentNG"));
        if(!WeaponComponent)
        {
            WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));
            WeaponComponent->bEditableWhenInherited = true;
            WeaponComponent->RegisterComponent();
    //        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP"));
        }
//    }
}

UWeaponManagerComponent::UWeaponManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    
    if(WeaponDefinitions)
    {
        WeaponDefinitions->RowStruct = FWeaponDefinition::StaticStruct();
    }
    
//    if(WeaponComponentNG)
//    {
////        UDbg::DbgMsg(FString("INITIALIZING WeaponComponentNG"));
////        TSubclassOf<class UWeaponComponentBase> It = WeaponManagerComponent->WeaponsArray[i];
////
////        if(It->IsChildOf(UWeaponComponentBase::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
////        {
////            if(It->GetClass() != UWeaponComponentBase::StaticClass() && !It->GetName().StartsWith(TEXT("SKEL_")))
////            {
////                UWeaponComponentBase* SpawnedWeapon = NewObject<UWeaponComponentBase>(WeaponManagerComponent->GetOwner(), It->GetDefaultObject()->GetClass());
////
//        WeaponComponent = NewObject<UWeaponComponent>(this, WeaponComponentNG->GetDefaultObject()->GetClass());
//        WeaponComponent->bEditableWhenInherited = true;
//        WeaponComponent->RegisterComponent();
////        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP"));
//    }
//    else
//    {
//        UDbg::DbgMsg(FString("NOOOOOOOOT INITIALIZING WeaponComponentNG"));
        if(!WeaponComponent)
        {
            WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponComponent>(this, TEXT("Weapon Component"));
            WeaponComponent->bEditableWhenInherited = true;
    //        UE_LOG(WeaponSysPlugin, Log, TEXT("WeaponComponent is SETUP (ObjectInitializer)"));
            WeaponComponent->RegisterComponent();
        }
//    }
}

void UWeaponManagerComponent::BeginPlay()
{
    Super::BeginPlay();
    
    int32 idx = 0;
    for(TSubclassOf<UBaseWeaponComponent> Weapon: WeaponArsenal)
    {
        UBaseWeaponComponent* NewWeapon = Cast<UBaseWeaponComponent>(Weapon->GetDefaultObject());
        
        UBaseWeaponComponent* NewWeaponImpl = NewObject<UBaseWeaponComponent>(this, NewWeapon->GetClass(), *NewWeapon->GetClass()->GetName());
            
//        NewWeaponImpl->OnProjectileFireDelegate.AddDynamic(this, &UWeaponManagerComponent::ProjectileFired);
//        NewWeaponImpl->OnProjectileHitDelegate.AddDynamic(this, &UWeaponManagerComponent::ProjectileHit);
        NewWeaponImpl->RegisterComponent();
        WeaponArsenalImpl.AddUnique(NewWeaponImpl);
        if(idx == 0)
        {
            CurrentWeapon = NewWeaponImpl;
        }
        idx++;
    }
//    this->SetCurrentWeapon(1, false);
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
//        WeaponComponent->StartShooting();
        if(CurrentWeapon)
        {
            CurrentWeapon->StartShooting(EWeaponFunction::Primary);
        }
    });
    PlayerInputComponent->KeyBindings.Add(KBP_PrimaryShootKey);
    
    FInputKeyBinding KBR_PrimaryShootKey(FInputChord(PrimaryShootKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_PrimaryShootKey.bConsumeInput = true;
    KBR_PrimaryShootKey.bExecuteWhenPaused = false;
    KBR_PrimaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
//        WeaponComponent->StopShooting();
        if(CurrentWeapon)
        {
            CurrentWeapon->StopShooting();
        }
    });
    InputComponent->KeyBindings.Add(KBR_PrimaryShootKey);
    
    FInputKeyBinding KBP_SecondaryShootKey(FInputChord(SecondaryShootKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_SecondaryShootKey.bConsumeInput = true;
    KBP_SecondaryShootKey.bExecuteWhenPaused = false;

    KBP_SecondaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
//        WeaponComponent->StartShooting(EWeaponFunction::Secondary);
        if(CurrentWeapon)
        {
            CurrentWeapon->StartShooting(EWeaponFunction::Secondary);
        }
    });
    PlayerInputComponent->KeyBindings.Add(KBP_SecondaryShootKey);
    
    FInputKeyBinding KBR_SecondaryShootKey(FInputChord(SecondaryShootKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_SecondaryShootKey.bConsumeInput = true;
    KBR_SecondaryShootKey.bExecuteWhenPaused = false;
    KBR_SecondaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
//        WeaponComponent->StopShooting();
        if(CurrentWeapon)
        {
            CurrentWeapon->StopShooting();
        }
    });
    InputComponent->KeyBindings.Add(KBR_SecondaryShootKey);
    
    // AlternateCrosshairKey
    FInputKeyBinding KBP_AlternateCrosshairKey(FInputChord(AlternateCrosshairKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_AlternateCrosshairKey.bConsumeInput = true;
    KBP_AlternateCrosshairKey.bExecuteWhenPaused = false;

    KBP_AlternateCrosshairKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
//        UDbg::DbgMsg(FString("AlternateCrosshairKey PRESSED"));
        WeaponComponent->OnAlternateCrosshair(true);
        //WeaponComponent->StartShooting(EWeaponFunction::Secondary);
    });
    PlayerInputComponent->KeyBindings.Add(KBP_AlternateCrosshairKey);
    
    FInputKeyBinding KBR_AlternateCrosshairKey(FInputChord(AlternateCrosshairKey, false, false, false, false), EInputEvent::IE_Released);
    KBR_AlternateCrosshairKey.bConsumeInput = true;
    KBR_AlternateCrosshairKey.bExecuteWhenPaused = false;
    KBR_AlternateCrosshairKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
//        UDbg::DbgMsg(FString("AlternateCrosshairKey RELEASED"));
        WeaponComponent->OnAlternateCrosshair(false);
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
                SetCurrentWeapon(WeaponDefinition->WeaponID);
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

void UWeaponManagerComponent::SetCurrentWeapon(int32 WeaponID, bool PlayAudio)
{
    if(!CurrentWeapon || CurrentWeapon->WeaponDefinition()->WeaponID != WeaponID)
    {
//        IsAimedAtChar = false;
//        IsAimedAtHitable = false;
//        IsAimedAtPickup = false;
        for(UBaseWeaponComponent* Weapon: WeaponArsenalImpl)
        {
            if(Weapon->WeaponDefinition()->WeaponID == WeaponID)
            {
//                if(IsReloading)
//                {
//                    IsReloading = false;
//                }
//
//                if(IsShooting)
//                {
//                    GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
//                }
//
                CurrentWeapon = Weapon;
//
//                AWeaponSystemCharacterBase* MyOwner = Cast<AWeaponSystemCharacterBase>(this->GetOwner());
//                if(CurrentWeapon && MyOwner && MyOwner->IsPlayerControlled())
//                {
//                    if(CurrentCSWidget)
//                    {
//                        CurrentCSWidget->RemoveFromViewport();
//                        CurrentCSWidget->Destruct();
//
//                        UDbg::DbgMsg(FString::Printf(TEXT("Removing Current CS Widget")), 5.0f, FColor::Green);
//                    }
//
//                    TSubclassOf<class UUserWidget> CSWidgetClass = CurrentWeapon->WeaponDefinition()->CrosshairUserWidget;
//
//                        if(CSWidgetClass)
//                        {
//                            UDbg::DbgMsg(FString::Printf(TEXT("HAS New CS Widget")), 5.0f, FColor::Green);
//
//                            CurrentCSWidget = CreateWidget<UUserWidget>(GetWorld(), CSWidgetClass);
//                            if (CurrentCSWidget)
//                            {
//                                UDbg::DbgMsg(FString::Printf(TEXT("Adding Current CS Widget")), 5.0f, FColor::Green);
//                                CurrentCSWidget->AddToViewport();
//                            }
//                        }
//                }
//
//                if(WeaponChangeSound && PlayAudio)
//                {
//                    UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, this->WeaponChangeSound, GetOwner()->GetActorLocation(), FRotator::ZeroRotator, 2.0, 1.0, 0.0f, nullptr, nullptr, true);
//                }
                break;
            }
        }
    }
}

void UWeaponManagerComponent::PickupWeapon(int32 WeaponID, int32 AmmoCount)
{
    UBaseWeaponComponent* const* DaWeapon = WeaponArsenalImpl.FindByPredicate( [&](UBaseWeaponComponent* Result){ return WeaponID == Result->WeaponDefinition()->WeaponID; } );
    
    if(DaWeapon)
    {
        UDbg::DbgMsg(FString::Printf(TEXT("PickupWeapon EXISTS AND FOUND")), 5.0f, FColor::Green);
        if(AmmoCount >= 0)
        {
            (*DaWeapon)->AmmoCount += AmmoCount;
        }
        
        if(CurrentWeapon->WeaponDefinition()->WeaponID != WeaponID)
        {
//            IsAimedAtChar = false;
//            IsAimedAtHitable = false;
//            IsAimedAtPickup = false;
            if(CurrentWeapon->IsShooting)
            {
                CurrentWeapon->StopShooting();
            }
        }
        
        SetCurrentWeapon(WeaponID, false);
    }
}
