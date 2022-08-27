//
//  WeaponManagerComponentBase.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponSystem/Definition/WeaponDefinition.h"
#include "WeaponSystem/BaseWeaponComponent.h"
//#include "WeaponSystem/HUD/WeaponSystemHUD.h"
#include "Utils/UtilityTimer.h"
#include "WeaponManagerComponentBase.generated.h"

DECLARE_DELEGATE(FSetupKeyDelegate)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlternateCrosshairDelegate, bool, Pressed);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEWEAPONSYSTEMPLUGIN_API UWeaponManagerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponentBase();
    UWeaponManagerComponentBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon System")
    FVector MuzzleOffset;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"))
    UDataTable* WeaponDefinitions;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey PrimaryShootKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey SecondaryShootKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey AlternateCrosshairKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey InitializeWeaponsKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<TSubclassOf<class UBaseWeaponComponent>> WeaponArsenal;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<class UBaseWeaponComponent*> WeaponArsenalImpl;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UWeaponComponent* WeaponComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon System")
    class UBaseWeaponComponent* CurrentWeapon;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsAimedAt = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsAimedAtHitable = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsAimedAtChar = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsAimedAtPickup = false;
    
//    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
//    bool IsAimedAtInt() {
//        bool bRet = false;
//        FHitResult HitResult;
//        this->IsAimedAt(bRet, HitResult);
//        return bRet;
//    }
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FHitResult HitResult;
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void PickupWeapon(int32 WeaponID, int32 AmmoCount);
    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    void SetupPlayerInput(class UInputComponent* PlayerInputComponent, class UInputComponent* InputComponent);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void SetCurrentWeapon(int32 WeaponID, bool PlayAudio = true);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    virtual void StartShooting(EWeaponFunction WeaponFunction = EWeaponFunction::Primary);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    virtual void StopShooting();

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnShotFired(FWeaponDefinition ShotWeaponDefinition, FWeaponFunctionDefinition ShotWeaponFunctionDefinition, EWeaponFunction ShotWeaponFunction);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void WeaponReloading(float Timeout);

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void InitializeWeapons();
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FWeaponReloadingDelegate OnWeaponReloading;

    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FOnAlternateCrosshairDelegate OnAlternateCrosshairDelegate;
};
