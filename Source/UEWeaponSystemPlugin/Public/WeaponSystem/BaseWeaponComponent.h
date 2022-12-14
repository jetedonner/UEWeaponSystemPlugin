//
//  BaseWeaponComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 07.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem/Definition/WeaponDefinition.h"
//#include "WeaponSystem/HUD/WeaponSystemHUD.h"
#include "Utils/UtilityTimer.h"
#include "Utils/Dbg.h"
#include "WeaponSystem/WeaponComponent.h"
#include "BaseWeaponComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponReloadingDelegate, float, Timeout);

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API UBaseWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UBaseWeaponComponent();

protected:

    FTimerHandle ReloadingEndTimerHandle;
    FTimerHandle ReloadingStartTimerHandle;
    
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FWeaponDefinition* CurrentWeaponDefinition;

    FTimerHandle ShootingTimerHandle;
    
    class UtilityTimer* TimerUtil = new UtilityTimer();
    
    // Called when the game starts
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsReloading = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinitionRowHandle;
    
    FWeaponDefinition* WeaponDefinition();
    
    EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon System")
    FVector MuzzleOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 InitialAmmoCount = 30;
    
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Weapon System")
    int32 _AmmoCount;

    UFUNCTION(BlueprintGetter)
    int32 GetAmmoCount()
    {
        return _AmmoCount; 
    }

    UFUNCTION(BlueprintSetter)
    void SetAmmoCount(int32 NewAmmoCount)
    {
        _AmmoCount = NewAmmoCount;
        
        AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
        if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
        {
            // if(!IsReloading)
            // {
            //     WeaponSystemHUD->InfoHUDWidget->OnShowReloadProgressBar(WeaponFunctionDefinition.Cadence);
            // }
            WeaponSystemHUD->InfoHUDWidget->AmmoCount = AmmoCount;
            WeaponSystemHUD->InfoHUDWidget->ClipAmmoCount = GetClipAmmoCount();// (AmmoCount %  WeaponDefinition()->ClipSize);// ClipAmmoCount;
        }
    }

    UPROPERTY(BlueprintReadWrite, BlueprintGetter=GetAmmoCount, BlueprintSetter=SetAmmoCount, Category="Weapon System")
    int32 AmmoCount;

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
    int32 GetClipAmmoCount()
    { 
        // UE_LOG(LogTemp, Warning, TEXT("GetClipAmmoCount() %d"), WeaponDefinition()->ClipSize);
        int32 ClipCount = AmmoCount % WeaponDefinition()->ClipSize;
        if(AmmoCount > 0)
        {
            if(ClipCount > 0)
            {
                return ClipCount;
            }
            else
            {
                return WeaponDefinition()->ClipSize;
            }
        }
        else
        {
            return AmmoCount;
        }
    }
    
    // UPROPERTY(BlueprintGetter=GetClipAmmoCount, Category="Weapon System")
    // int32 ClipAmmoCount;
    
    // UPROPERTY(BlueprintGetter=GetClipAmmoCount, Category="Weapon System")
    // int32 ClipAmmoCount;
    
    // UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
    // int32 GetClipAmmoCount()
    // {
    //     if(AmmoCount > 0)
    //     {
    //         int32 ClipAmmoCountVar = AmmoCount % WeaponDefinition()->ClipSize;
            
    //         UDbg::DbgMsg(FString::Printf(TEXT("WeaponDefinition()->ClipSize %d"), WeaponDefinition()->ClipSize), 5.0f, FColor::Purple);

    //         if(ClipAmmoCountVar == 0)
    //         {
    //             return WeaponDefinition()->ClipSize;
    //         }
    //         else
    //         {
    //             return ClipAmmoCountVar;
    //         }
    //         // return AmmoCount % WeaponDefinition()->ClipSize;
    //     }
    //     else
    //     {
    //         UDbg::DbgMsg(FString::Printf(TEXT("WeaponDefinition()->ClipSize %d"), WeaponDefinition()->ClipSize), 5.0f, FColor::Purple);
    //         return AmmoCount;
    //     }
    // }
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UAudioComponent* ShotAudioComponent;
    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void StartShooting(EWeaponFunction WeaponFunction = EWeaponFunction::Primary);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void StopShooting();
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void FireShot();
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void StartReloading();
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void FinishReloading();
    
    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System")
    void OnCustomStartShooting(FWeaponDefinition ShotWeaponDefinition, FWeaponFunctionDefinition ShotWeaponFunctionDefinition, EWeaponFunction ShotWeaponFunction, bool& Handled);
    
    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System")
    void OnShotFired(FWeaponDefinition ShotWeaponDefinition, FWeaponFunctionDefinition ShotWeaponFunctionDefinition, EWeaponFunction ShotWeaponFunction, bool& Handled);

    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System")
    void OnCustomStopShooting(FWeaponDefinition ShotWeaponDefinition, FWeaponFunctionDefinition ShotWeaponFunctionDefinition, EWeaponFunction ShotWeaponFunction, bool& Handled);
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FOnShotFiredDelegate OnShotFiredDelegate;
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FWeaponReloadingDelegate OnWeaponReloading;

    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FOnProjectileFiredDelegate OnProjectileFired;
    
};
