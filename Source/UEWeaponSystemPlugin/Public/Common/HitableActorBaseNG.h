

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Common/HitableInterface.h"
#include "Utils/Dbg.h"
#include "HitableActorBaseNG.generated.h"

UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AHitableActorBaseNG : public AActor, public IHitableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitableActorBaseNG();
    AHitableActorBaseNG(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    class UShapeComponent* CollisionComponent;
    
    UFUNCTION()
    void AttachMesh();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    class UStaticMeshComponent* MeshComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon System")
    void OnGotHitted();
    // void OnGotHitted(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    virtual void OnGotHitted_Implementation();


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon System")
    void OnHitted(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    virtual void OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
