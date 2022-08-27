//
//  WeaponSystemCharacter.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponSystem/WeaponManagerComponentExt.h"
#include "Score/ScoreManagerComponent.h"
#include "Health/HealthManagerComponent.h"
#include "Utils/GlobalDefinitions.h"
#include "Utils/Dbg.h"
#include "Common/HitableInterface.h"
#include "WeaponSystemCharacter.generated.h"

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemCharacter : public ACharacter, public IHitableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWeaponSystemCharacter();
    AWeaponSystemCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UWeaponManagerComponentExt* WeaponManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    UHealthManagerComponent* HealthManagerComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite /*EditAnywhere, BlueprintReadWrite*/, Category="Weapon System")
    class UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    UScoreManagerComponent* ScoreManagerComponent;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
	USceneComponent* MuzzlePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* DieSound;
    
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon System")
    void OnHitted(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    virtual void OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};
