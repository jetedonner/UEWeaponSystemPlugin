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
#include "WeaponSystem/WeaponManagerComponent.h"
#include "Score/ScoreManagerComponent.h"
#include "Health/HealthManagerComponent.h"
#include "Utils/GlobalDefinitions.h"
#include "Utils/Dbg.h"
#include "WeaponSystemCharacter.generated.h"

UCLASS(Blueprintable)
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemCharacter : public ACharacter
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
    UWeaponManagerComponent* WeaponManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    UHealthManagerComponent* HealthManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UWidgetComponent* FloatingHealthBar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    UScoreManagerComponent* ScoreManagerComponent;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
	USceneComponent* MuzzlePosition;
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
    
};
