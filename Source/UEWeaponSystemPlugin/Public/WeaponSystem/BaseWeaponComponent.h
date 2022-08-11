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
#include "Utils/UtilityTimer.h"
#include "BaseWeaponComponent.generated.h"


UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API UBaseWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UBaseWeaponComponent();

protected:
    
    bool IsReloading = false;
    FTimerHandle ReloadingEndTimerHandle;
    FTimerHandle ReloadingStartTimerHandle;

    FTimerHandle ShootingTimerHandle;
    
    class UtilityTimer* TimerUtil = new UtilityTimer();
    
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinitionRowHandle;
    
    FWeaponDefinition* WeaponDefinition();
    
    EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;
    
    
    
//    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
//    FWeaponDefinition GetWeaponDefinition()
//    {
//        return *WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
//    }
    
//    FWeaponDefinition* FoundWeaponDefinition = WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
//    FWeaponDefinition* FoundWeaponDefinition = WeaponDefinition.DataTable->FindRow<FWeaponDefinition>(WeaponDefinition.RowName, "");
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 InitialAmmoCount = 30;
    
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Weapon System")
    int32 AmmoCount;
    
    UPROPERTY(BlueprintGetter=GetClipAmmoCount, Category="Weapon System")
    int32 ClipAmmoCount;
    
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
    int32 GetClipAmmoCount()
    {
        if(AmmoCount > 0)
        {
            int32 ClipAmmoCountVar = AmmoCount % WeaponDefinition()->ClipSize;
            if(ClipAmmoCountVar == 0)
            {
                return WeaponDefinition()->ClipSize;
            }
            else
            {
                return ClipAmmoCountVar;
            }
            return AmmoCount % WeaponDefinition()->ClipSize;
        }
        else
        {
            return AmmoCount;
        }
    }
    
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
};
