//
//  WeaponSystemProjectileRadial.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 22.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "WeaponSystem/Projectiles/WeaponSystemProjectile.h"
#include "WeaponSystemProjectileRadial.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemProjectileRadial : public AWeaponSystemProjectile
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AWeaponSystemProjectileRadial();
    AWeaponSystemProjectileRadial(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    bool ApplyRadialDamage = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
	class URadialForceComponent* RadialForceComponent;

	// UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

};
