//
//  WeaponSystemProjectileRadial.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 22.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Projectiles/WeaponSystemProjectileRadial.h"

AWeaponSystemProjectileRadial::AWeaponSystemProjectileRadial():Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!RadialForceComponent)
    {
        // Use a sphere as a simple collision representation.
        RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("SphereComponent"));
        RadialForceComponent->SetupAttachment(CollisionComponent);
        RadialForceComponent->Radius = 500.0f;
        // Set the sphere's collision profile name to "Projectile".
        // CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        // CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponSystemProjectile::OnHit);
        // Set the sphere's collision radius.
        // CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        // RootComponent = CollisionComponent;
    }
    
}

AWeaponSystemProjectileRadial::AWeaponSystemProjectileRadial(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    if (!RadialForceComponent)
    {
        // Use a sphere as a simple collision representation.
        RadialForceComponent = ObjectInitializer.CreateDefaultSubobject<URadialForceComponent>(this, TEXT("RadialForceComponent"));
        RadialForceComponent->SetupAttachment(CollisionComponent);
        RadialForceComponent->Radius = 500.0f;
        // Set the sphere's collision profile name to "Projectile".
        // CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        // CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponSystemProjectile::OnHit);
        // Set the sphere's collision radius.
        // CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        // RootComponent = CollisionComponent;
    }
}

void AWeaponSystemProjectileRadial::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
    
    RadialForceComponent->FireImpulse();

    TArray<AActor*> IgnoredActors;

    UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageFactor,
		GetActorLocation(),
		RadialForceComponent->Radius,
		UDamageType::StaticClass(),
		IgnoredActors,
		this,
		nullptr,
		false,
		ECollisionChannel::ECC_Visibility);

    // UDbg::DbgMsg(FString::Printf(TEXT("AWeaponSystemProjectileRadial => Projectile OnHit: %s / Owner: %s"), *OtherActor->GetName(), *this->GetOwner()->GetName()));
}