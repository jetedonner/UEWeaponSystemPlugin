

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Score/MovingScoreWidgetBase.h"
#include "Score/ScoreHelper.h"
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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool SpawnAtRandomLocation = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool RespawnAfterPickup = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(UIMin="3.0", UIMax="900.0", EditCondition="RespawnAfterPickup"))
    float RespawnTimeout;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(EditCondition="RespawnAfterPickup"))
    FFloatRange RespawnTimeoutRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool HasScore = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit", meta=(EditCondition="HasScore"))
    float HitScore = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit", meta=(EditCondition="HasScore"))
    bool ShowMovingScoreWidget = true;
    
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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinition;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 PickUpCount = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* PickupSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    class UParticleSystemComponent* ParticleSystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    class UParticleSystem* PickupEffect;
    
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // class UParticleSystemComponent* ParticleSystemComponent;

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnPickup(AActor* OtherActor);
};
