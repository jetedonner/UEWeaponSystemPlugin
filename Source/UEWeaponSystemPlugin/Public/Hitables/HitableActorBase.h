//
//  HitableActorBase.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Utils/Dbg.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utils/GlobalDefinitions.h"
#include "WeaponSystem/Player/WeaponSystemCharacter.h"
#include "Score/MovingScoreWidgetBase.h"
#include "Score/ScoreHelper.h"
#include "Common/HitableInterface.h"
#include "HitableActorBase.generated.h"

UCLASS(Abstract, Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API AHitableActorBase : public AActor, public IHitableInterface
{
    GENERATED_BODY()
    
public:
    
    AHitableActorBase();
    AHitableActorBase(const FObjectInitializer& ObjectInitializer);
    
protected:

    virtual void BeginPlay() override;

public:

    virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool AllowMultipleHits = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool ByPassTriggeringActors = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool ShowMovingScoreWidget = true;
    
    bool IsHit = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    float HitScore = 100.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool DestroyOnHit = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    class UShapeComponent* CollisionComponent;
    
    UFUNCTION()
    void AttachMesh();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    class UStaticMeshComponent* MeshComponent;
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    UFUNCTION(BlueprintCallable, Category="Event|Hit")
    virtual void ExecActorHitHandler(AActor* OtherActor, const FHitResult& Hit);
    
    UFUNCTION(BlueprintNativeEvent, Category="Event|Hit")
    void OnComponentGotHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
    
    void OnComponentGotHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon System")
    void OnHitted(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    virtual void OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
