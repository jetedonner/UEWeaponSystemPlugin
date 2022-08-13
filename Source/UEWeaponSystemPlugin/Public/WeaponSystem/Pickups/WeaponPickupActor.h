

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "WeaponPickupActor.generated.h"

UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AWeaponPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickupActor();
    AWeaponPickupActor(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    
    
//    void SetPickUpCount();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    class UStaticMeshComponent* StaticMeshComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    class USphereComponent* CollisionSphere;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    class URotatingMovementComponent* RotatingMovement;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    FRotator RotationRate = FRotator(0, 300, 0);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    float CollisionRadius = 100.0f;
    
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
//    UParticleSystemComponent* ParticleSystemComponent;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
//    UParticleSystem* PickupEffect;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinition;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 PickUpCount = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* PickupSound;
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnPickup(AActor* OtherActor);
};