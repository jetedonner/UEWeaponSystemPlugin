//
//  WeaponComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 07.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/UtilityTimer.h"
#include "WeaponSystem/Definition/WeaponDefinition.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlternateCrosshairDelegate, bool, Pressed);
//RamaMeleeWeapon class .h

//DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(bool, FOnCustomStartShooting, FWeaponDefinition, WeaponDefinition, FWeaponFunctionDefinition, WeaponFunctionDefinition, EWeaponFunction, WeaponFunction);

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();
    UWeaponComponent(const FObjectInitializer& ObjectInitializer);

protected:
    
    bool IsReloading = false;
    FTimerHandle ReloadingEndTimerHandle;
    FTimerHandle ReloadingStartTimerHandle;

    bool IsShooting = false;
    FTimerHandle ShootingTimerHandle;
    
    class UtilityTimer* TimerUtil = new UtilityTimer();
    
	// Called when the game starts
	virtual void BeginPlay() override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"))
    UDataTable* WeaponDefinitions;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    struct FWeaponDefinition CurrentWeaponDefinition;
    
    EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;
    
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
    FWeaponFunctionDefinition GetWeaponFunctionDefinition(EWeaponFunction WeaponFunction)
    {
        if(WeaponFunction == EWeaponFunction::Secondary)
        {
            return CurrentWeaponDefinition.SecondaryWeaponFunctionDefinition;
        }
        else
        {
            return CurrentWeaponDefinition.PrimaryWeaponFunctionDefinition;
        }
    }
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UAudioComponent* ShotAudioComponent;
    
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void SetCurrentWeapon(struct FWeaponDefinition& WeaponDefinition);
    
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
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnAlternateCrosshair(bool Pressed);
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FOnAlternateCrosshairDelegate OnAlternateCrosshairDelegate;
    
//    UPROPERTY(BlueprintAssignable, Category="Weapon System")
//    FOnCustomStartShooting OnCustomStartShooting;
    
//    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System")
//    void OnCustomStartShooting(FWeaponDefinition WeaponDefinition, FWeaponFunctionDefinition WeaponFunctionDefinition, EWeaponFunction WeaponFunction, bool& Handled);
    
};
