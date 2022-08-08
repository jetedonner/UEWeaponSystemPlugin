//
//  WeaponManagerComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem/Definition/WeaponDefinition.h"
#include "WeaponSystem/BaseWeaponComponent.h"
#include "WeaponManagerComponent.generated.h"

DECLARE_DELEGATE(FSetupKeyDelegate)

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();
    UWeaponManagerComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"))
    UDataTable* WeaponDefinitions;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey PrimaryShootKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey SecondaryShootKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey AlternateCrosshairKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<TSubclassOf<class UBaseWeaponComponent>> WeaponArsenal;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<class UBaseWeaponComponent*> WeaponArsenalImpl;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UWeaponComponent* WeaponComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon System")
    class UBaseWeaponComponent* CurrentWeapon;
    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    void SetupPlayerInput(class UInputComponent* PlayerInputComponent, class UInputComponent* InputComponent);
    
    void SetCurrentWeapon(int32 WeaponID, bool PlayAudio = true);
};
