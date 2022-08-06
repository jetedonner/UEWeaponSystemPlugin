//
//  WeaponSystemProjectile.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 07.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "WeaponSystem/Definition/DecalStruct.h"
#include "WeaponSystemProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProjectileHitDelegate, AActor*, ProjectileActor, AActor*, OtherActor, FVector, Location);

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponSystemProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
//    UPROPERTY()
//    FWeaponFunctionDefinition WeaponFunctionDefinition;
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    bool DestroyOnHit = true;
    
    // Function that is called when the projectile hits something.
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FProjectileHitDelegate OnProjectileHitDelegate;

    // Sphere collision component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
    USphereComponent* CollisionComponent;

    // Projectile movement component
    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    // Projectile mesh
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* ProjectileMeshComponent;

    // Projectile material
    UPROPERTY(VisibleDefaultsOnly, Category = Movement)
    UMaterialInstanceDynamic* ProjectileMaterialInstance;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UParticleSystem* ImpactEffect;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* ImpactTargetSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* ImpactFailSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<FDecalStruct> ImpactDecals;
    
    UPROPERTY(BlueprintReadOnly, Category="Weapon System")
    class UDecalComponent* ImpactDecalObject;
    
    // Function that initializes the projectile's velocity in the shoot direction.
    void FireInDirection(const FVector& ShootDirection);

};
