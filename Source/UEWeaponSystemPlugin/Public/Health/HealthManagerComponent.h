//
//  UHealthManagerComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Utils/Dbg.h"
#include "Health/FloatingHealthBarWidget.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "WeaponSystem/HUD/WeaponSystemHUD.h"
#include "Health/FloatingHealthBarWidgetComponent.h"
#include "HealthManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FReceivedAnyDamageDelegate, float, Damage, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEWEAPONSYSTEMPLUGIN_API UHealthManagerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupParent(ACharacter* InParent);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    float Health = 100.0f;
    
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Health System")
    bool GetDied()
	{
		return (Health <= 0.0f);
	}

	UPROPERTY(BlueprintGetter=GetDied, Category="Health System")
    bool Died;

   	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
   	UFloatingHealthBarWidget* FloatingHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
   	UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponentInst;

	UPROPERTY(EditAnywhere, Category="Health System", meta=(UseComponentPicker, AllowedClasses="UFloatingHealthBarWidget"))
	FComponentReference FloatingHealthBarWidgetComponent;
    
    UFUNCTION(BlueprintCallable, Category="Health System")
    void IncreaseHealth(float Value, float& NewHealth);
    
    UFUNCTION(BlueprintCallable, Category="Health System")
    void DecreaseHealth(float Value, float& NewHealth);

	UFUNCTION(BlueprintCallable, Category="Health System")
	void SetHealth(float Value);
    
	UPROPERTY(BlueprintAssignable, Category="Health System")
    FReceivedAnyDamageDelegate OnReceivedAnyDamageDelegate;

    UFUNCTION(BlueprintCallable, Category="Health System")
    void ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
