

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HitableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHitableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UEWEAPONSYSTEMPLUGIN_API IHitableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//UFUNCTION(BlueprintNativeEvent, Category="Event|Hit")
    // virtual void OnGotHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

    // UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon System")
    // void OnGotHitted();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon System")
    void OnHitted(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
