

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/WeaponManagerComponentBase.h"
#include "Utils/UtilityTimer.h"
#include "WeaponManagerComponentExt.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UWeaponManagerComponentExt : public UWeaponManagerComponentBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FTimerHandle ShootingTimerHandle;
    
    class UtilityTimer* TimerUtil = new UtilityTimer();

	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsReloading = false;

	EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;

	// UFUNCTION(BlueprintCallable, Category="Weapon System")
    virtual void StartShooting(EWeaponFunction WeaponFunction = EWeaponFunction::Primary) override;
    
    // UFUNCTION(BlueprintCallable, Category="Weapon System")
    virtual void StopShooting() override;
};
