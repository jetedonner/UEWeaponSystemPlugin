//
//  WeaponSystemProjectile.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 07.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/WeaponSystemProjectile.h"

// Sets default values
AWeaponSystemProjectile::AWeaponSystemProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision profile name to "Projectile".
        CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponSystemProjectile::OnHit);
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 3000.0f;
        ProjectileMovementComponent->MaxSpeed = 3000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        ProjectileMeshComponent->SetupAttachment(RootComponent);
    }
    
    InitialLifeSpan = 0.0f;
}

AWeaponSystemProjectile::AWeaponSystemProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    
    if (!RootComponent)
    {
        RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
        // Set the sphere's collision profile name to "Projectile".
        CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponSystemProjectile::OnHit);
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 3000.0f;
        ProjectileMovementComponent->MaxSpeed = 3000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ProjectileMeshComponent"));
        ProjectileMeshComponent->SetupAttachment(RootComponent);
    }
    
    InitialLifeSpan = 0.0f;
}

// Called when the game starts or when spawned
void AWeaponSystemProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponSystemProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponSystemProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UDbg::DbgMsg(FString::Printf(TEXT("Projectile OnHit: %s / Owner: %s"), *OtherActor->GetName(), *this->GetOwner()->GetName()));
    if(OtherActor == this->GetOwner())
    {
        return;
    }


    if(OtherActor->Implements<UHitableInterface>())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("OtherActor->Implements<UHitableInterface>() IIIIIITTTTTT IMPLEMENTS !!!!!!!!!!!!")));
    }

    if (OtherActor != nullptr && OtherActor != this && OtherComponent != nullptr)
    {
        if(OtherComponent->IsSimulatingPhysics())
        {
            OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
        }
        UGameplayStatics::ApplyDamage(OtherActor, DamageFactor, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
    }
    
    if(ImpactTargetSound)
    {
//        UDbg::DbgMsg(FString::Printf(TEXT("Projectile ImpactTargetSound IS SET")));
        UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, ImpactTargetSound, Hit.ImpactPoint, FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("Projectile ImpactTargetSound IS NOT SET")));
    }
    
    if(ImpactEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), FRotator(1), true, EPSCPoolMethod::AutoRelease, true);
    }
    
    if(ImpactDecals.Num() > 0)
    {
        int32 Idx = FMath::RandRange(0, ImpactDecals.Num() - 1);
        
        FDecalStruct ImpactDecal = ImpactDecals[Idx];
        UMaterialInterface* Decal = Cast<UMaterialInterface>(ImpactDecal.ImpactDecalMaterial);
        
        FVector DecalLocation = Hit.ImpactPoint;
        
        FRotator RandomDecalRotation = UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal);
        RandomDecalRotation.Roll += FMath::RandRange(-180.0f, 180.0f);
        
        float RandDecalLifeSpan = FMath::RandRange(ImpactDecal.DecalLifeSpanMin, ImpactDecal.DecalLifeSpanMax);
        
        ImpactDecalObject = UGameplayStatics::SpawnDecalAttached(Decal, ImpactDecal.DecalSize, OtherComponent, "", DecalLocation, RandomDecalRotation, EAttachLocation::KeepWorldPosition, RandDecalLifeSpan);
        
        if(ImpactDecal.DecalFadeOutEffect)
        {
            ImpactDecalObject->SetFadeOut(RandDecalLifeSpan - ImpactDecal.DecalFadeOutDuration, ImpactDecal.DecalFadeOutDuration, false);
        }
    }
    
    this->OnProjectileHitDelegate.Broadcast(this, OtherActor, Hit.Location);
    
    if(DestroyOnHit)
    {
        this->Destroy();
    }
//    Destroy();
}

// Function that initializes the projectile's velocity in the shoot direction.
void AWeaponSystemProjectile::FireInDirection(const FVector& ShootDirection)
{
    LineTraceProjectile();
    
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
    
//    if(ShotSound)
//    {
//        ShotAudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, ShotSound, GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
//    }
}

void AWeaponSystemProjectile::LineTraceProjectile()
{
    APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
    if (CameraManager)
    {
//        FVector Start = CameraManager->GetCameraLocation() + FVector(100.0f, 0.0f, 0.0f);
        AActor* ActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();
        // Get the camera transform.
        FVector CameraLocation;
        FRotator CameraRotation;
        ActorRef->GetActorEyesViewPoint(CameraLocation, CameraRotation);

        FVector MuzzleOffset;
        // Set MuzzleOffset to spawn projectiles slightly in front of the camera.
        MuzzleOffset.Set(70.0f, 0.0f, 0.0f);

        // Transform MuzzleOffset from camera space to world space.
        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

        // Skew the aim to be slightly upwards.
//        FRotator MuzzleRotation = CameraRotation;
        FVector Start = MuzzleLocation;
        FVector End = Start + 10000.0 * CameraManager->GetActorForwardVector();
        
        bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1);

        if (isHit)
        {
            bool HitCharacterOrHitable = false;
            if(Cast<AWeaponSystemCharacter>(HitResult.GetActor()) || Cast<AHitableActorBase>(HitResult.GetActor()))
            {
                UDbg::DbgMsg(FString::Printf(TEXT("Projectile LINETRACE HIT Char Or Hitable")));
                HitCharacterOrHitable = true;
            }
            OnLineTraceHit(HitResult, HitCharacterOrHitable);
        }
    }
}
