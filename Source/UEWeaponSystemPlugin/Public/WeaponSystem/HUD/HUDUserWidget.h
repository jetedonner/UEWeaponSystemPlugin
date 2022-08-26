

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
// #include "WeaponSystem/Player/WeaponSystemCharacter.h"
#include "HUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    // AWeaponSystemCharacter* WeaponSystemCharacter;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    int32 AmmoCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    int32 ClipAmmoCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    float Score;

    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System|HUD")
    void OnShowReloadProgressBar(float ReloadTime);
};
