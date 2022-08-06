//
//  WeaponSystemCharacter.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponSystem/WeaponManagerComponent.h"
#include "Utils/GlobalDefinitions.h"
#include "Utils/Dbg.h"
#include "WeaponSystemCharacter.generated.h"

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWeaponSystemCharacter();
    AWeaponSystemCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UWeaponManagerComponent* WeaponManagerComponent;
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    
};
