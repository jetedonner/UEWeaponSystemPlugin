


#include "WeaponSystem/Pickups/WeaponPickupActor.h"

// Sets default values
AWeaponPickupActor::AWeaponPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Sets default values
AWeaponPickupActor::AWeaponPickupActor(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if(!CollisionSphere)
    {
        CollisionSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Collision Sphere Component"));
        CollisionSphere->InitSphereRadius(CollisionRadius);
        CollisionSphere->SetMobility(EComponentMobility::Movable);
        CollisionSphere->SetNotifyRigidBodyCollision(true);
        CollisionSphere->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        CollisionSphere->SetRelativeLocation_Direct(FVector(0.0f, 0.0f, CollisionRadius));
//        CollisionSphere->SetupAttachment(RootComponent);
        RootComponent = CollisionSphere;
    }
    
    if(!StaticMeshComponent){
        StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Weapon Pickup Mesh"));
        StaticMeshComponent->SetMobility(EComponentMobility::Movable);
        StaticMeshComponent->SetupAttachment(CollisionSphere);
    }
    
//    if(!ParticleSystemComponent)
//    {
//        ParticleSystemComponent = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystemComponent"));
//        //ParticleSystemComponent->SetMobility(EComponentMobility::Movable);
//        ParticleSystemComponent->SetRelativeLocation_Direct(FVector(0.0f, 0.0f, -CollisionRadius));
//        ParticleSystemComponent->SetupAttachment(CollisionSphere);
//    }

    if(!RotatingMovement)
    {
        // Create movement component and set rotation rate
        RotatingMovement = ObjectInitializer.CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
        RotatingMovement->SetUpdatedComponent(StaticMeshComponent);
        RotatingMovement->RotationRate = RotationRate;
    }
}

// Called when the game starts or when spawned
void AWeaponPickupActor::BeginPlay()
{
	Super::BeginPlay();
	
    if(RotatingMovement)
    {
        RotatingMovement->RotationRate = RotationRate;
    }
    
    CollisionSphere->OnComponentHit.AddDynamic(this, &AWeaponPickupActor::OnHit);
}

// Called every frame
void AWeaponPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponPickupActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // UDbg::DbgMsg(FString::Printf(TEXT("AWeaponPickupActor::OnHit(...) by => %s"), *OtherActor->GetName()), 5.0f, FColor::Red);
    
    AWeaponSystemCharacter* PickupCharacter = Cast<AWeaponSystemCharacter>(OtherActor);
    if(PickupCharacter)
    {
        // UDbg::DbgMsg(FString::Printf(TEXT("PickupCharacter FOUND => PiuckingUp")), 5.0f, FColor::Red);
        this->OnPickup(PickupCharacter);
    }
    else
    {
        // UDbg::DbgMsg(FString::Printf(TEXT("PickupCharacter NOT Found => Trying Projectile")), 5.0f, FColor::Red);
        AWeaponSystemProjectile* PickupProjectile = Cast<AWeaponSystemProjectile>(OtherActor);
        if(PickupProjectile)
        {
            // UDbg::DbgMsg(FString::Printf(TEXT("AWeaponPickupActorBase::OnHit(...) PROJECTILE => %s"), *OtherActor->GetName()), 5.0f, FColor::Red);
            
            APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
            this->OnPickup(PlayerPawn);
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("Hit Pickup Actor is NOT a CHARACTER and NOT a PROJECTILE => IGNORING")), 5.0f, FColor::Red);
        }
    }
}

void AWeaponPickupActor::OnPickup(AActor* OtherActor)
{
    AWeaponSystemCharacter* PickupCharacter = Cast<AWeaponSystemCharacter>(OtherActor);
    if(PickupCharacter)
    {
        FWeaponDefinition* CurrentWeaponDefinition = WeaponDefinition.GetRow<FWeaponDefinition>("");
        
        if(CurrentWeaponDefinition)
        {
            int32 DefPickUpCount = (PickUpCount < 0 ? CurrentWeaponDefinition->PickUpCount : PickUpCount);
            PickupCharacter->WeaponManagerComponent->PickupWeapon(CurrentWeaponDefinition->WeaponID, DefPickUpCount);
            if(PickupSound)
            {
                UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
            }
            
//            if(PickupEffect)
//            {
//                FVector PickupEffectLocation = GetActorLocation();
//                PickupEffectLocation.Z -= CollisionRadius;
//
//                UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupEffect, PickupEffectLocation, FRotator(1), true, EPSCPoolMethod::AutoRelease, true);
//
//                UDbg::DbgMsg(FString::Printf(TEXT("PickupEffect FOUND")), 5.0f, FColor::Red, true);
//            }
//            else
//            {
//                UDbg::DbgMsg(FString::Printf(TEXT("PickupEffect NOT Found")), 5.0f, FColor::Red);
//            }
            
            this->Destroy();
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("WeaponDefinition NOT FOUND (You must specify a WeaponDefinition for this Weapon!) => %s"), *WeaponDefinition.RowName.ToString()), 5.0f, FColor::Red);
        }
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("PickupCharacter NOT NOT Found => %s"), *OtherActor->GetName()), 5.0f, FColor::Yellow);
    }
}
